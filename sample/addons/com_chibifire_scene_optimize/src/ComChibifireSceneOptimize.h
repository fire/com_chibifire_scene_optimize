// Copyright (c) 2007-2017 Juan Linietsky, Ariel Manzur.
// Copyright (c) 2014-2017 Godot Engine contributors (cf. AUTHORS.md)

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// -- Godot Engine <https://godotengine.org>

#pragma once

#include "core/Godot.hpp"
#include "gen/ArrayMesh.hpp"
#include "gen/EditorScenePostImport.hpp"
#include "gen/Mesh.hpp"
#include "gen/MeshDataTool.hpp"
#include "gen/MeshInstance.hpp"
#include "gen/Node.hpp"
#include "gen/Spatial.hpp"
#include "gen/SurfaceTool.hpp"
#include "openvdb/openvdb.h"
#include <MeshToVolume.h>
#include <VolumeToMesh.h>
#include <vector>

typedef std::vector<int32_t> MeshDataFace;

struct MeshDataAdapter {
	std::vector<openvdb::Vec3d> vertices;
	std::vector<openvdb::Vec2d> uvs;
	std::vector<MeshDataFace> faces;

	inline size_t polygonCount() const { return faces.size(); };
	inline size_t pointCount() const { return vertices.size(); };
	inline size_t vertexCount(size_t n) const { return faces[n].size(); };

	inline void getIndexSpacePoint(size_t n, size_t v, openvdb::Vec3d &pos) const {
		pos = vertices[faces[n][v]];
	}
};

using namespace std;
using namespace godot;

class ComChibifireSceneOptimize : public godot::EditorScenePostImport {
private:
	GODOT_CLASS(ComChibifireSceneOptimize, EditorScenePostImport);

public:
	godot::Object *post_import(godot::Object *p_node) {
		Node *node = Node::cast_to<Node>(p_node);
		Array arr;
		arr = _find_mesh_instances(node, arr);
		for (int32_t i = 0; i < arr.size(); i++) {
			MeshInstance *mi = Object::cast_to<MeshInstance>(arr[i]);
			const double voxel_size = 1.0f;
			const double inv_voxel_size = 1.0f / voxel_size;
			const double bandwidth = 10.0f;
			Ref<MeshDataTool> mdt = MeshDataTool::_new();
			Ref<ArrayMesh> arr_mesh = ArrayMesh::_new();
			for (int32_t j = 0; j < mi->get_surface_material_count(); j++) {
				Ref<ArrayMesh> godot_mesh = mi->get_mesh();
				mdt->create_from_surface(godot_mesh, j);
				MeshDataAdapter vdb_mesh;
				for (int32_t k = 0; k < mdt->get_vertex_count(); k++) {
					openvdb::Vec2d uv = openvdb::Vec2d(mdt->get_vertex_uv(k).x, mdt->get_vertex_uv(k).y);
					vdb_mesh.uvs.push_back(uv);

					Vector3 vert = mdt->get_vertex(k);
					vdb_mesh.vertices.push_back(openvdb::Vec3d(vert.x * inv_voxel_size, vert.y * inv_voxel_size, vert.z * inv_voxel_size));
				}
				for (int32_t k = 0; k < mdt->get_face_count(); k++) {
					MeshDataFace face;
					for (int32_t l = 0; l < 3; l++) {
						//32 bit indexes only?
						int32_t index = (int32_t)mdt->get_face_vertex(k, l);
						face.push_back(index);
					}
					vdb_mesh.faces.push_back(face);
				}
				openvdb::FloatGrid::Ptr volume = openvdb::tools::meshToVolume<openvdb::FloatGrid, MeshDataAdapter>(vdb_mesh, openvdb::math::Transform(), bandwidth, bandwidth, 0, NULL);
				volume->setTransform(openvdb::math::Transform::createLinearTransform(voxel_size));
				double isovalue = 0.0;
				double adaptivity = 0.5;
				isovalue /= volume->voxelSize().x();
				std::vector<openvdb::Vec3s> points;
				std::vector<openvdb::Vec3I> triangles;
				std::vector<openvdb::Vec4I> quads;
				openvdb::tools::volumeToMesh<openvdb::FloatGrid>(*volume, points, triangles, quads, isovalue, adaptivity);
				if (!quads.size()) {
					continue;
				}
				Ref<SurfaceTool> st = SurfaceTool::_new();

				for (int m = 0; m < triangles.size(); m++) {
					st->add_index(triangles[m].z());
					st->add_index(triangles[m].y());
					st->add_index(triangles[m].x());
				}

				//https://stackoverflow.com/a/43422763/381724
				for (int m = 0; m < quads.size(); m++) {
					vector<int> quad_points;
					quad_points.push_back(quads[m].x());
					quad_points.push_back(quads[m].y());
					quad_points.push_back(quads[m].z());
					quad_points.push_back(quads[m].w());
					int n = 0;
					st->add_index(quad_points[2]);
					st->add_index(quad_points[1]);
					st->add_index(quad_points[0]);
					for (i = 3; i < quad_points.size(); i++) {
						st->add_index(quad_points[i]);
						st->add_index(quad_points[i - 1]);
						st->add_index(quad_points[i - 3]);
					}
				}
				st->begin(Mesh::PRIMITIVE_TRIANGLES);
				for (int m = 0; m < points.size(); m++) {
					Vector3 vec;
					vec.x = points[m].x();
					vec.y = points[m].y();
					vec.z = points[m].z();
					st->add_vertex(vec);
				}
				mi->set_mesh(st->commit());
			}
			// Next feature
			// UVs, Normals and bone data
			return node;
		}
	}

	Array _find_mesh_instances(Node *p_node, Array &p_arr) {
		for (size_t i = 0; i < p_node->get_child_count(); i++) {
			MeshInstance *mi = Node::cast_to<MeshInstance>(p_node->get_child(i));
			if (mi != NULL) {
				p_arr.push_back(mi);
			}
			_find_mesh_instances(p_node->get_child(i), p_arr);
		}
		return p_arr;
	}

	ComChibifireSceneOptimize() {
	}
	void _init() {
		openvdb::initialize();
	}
	static void _register_methods() {
		register_method("post_import", &ComChibifireSceneOptimize::post_import);
	}
};
