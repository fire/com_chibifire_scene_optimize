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
#include "openvdb/openvdb.h"
#include <MeshToVolume.h>

typedef std::vector<int> MeshDataFace;

struct MeshDataAdapter {
  std::vector<openvdb::Vec3d> vertices;
  std::vector<MeshDataFace> faces;

  inline size_t polygonCount() const { return faces.size(); };
  inline size_t pointCount() const { return vertices.size(); }; 
  inline size_t vertexCount(size_t n) const { return faces[n].size(); };

  inline void getIndexSpacePoint(size_t n, size_t v, openvdb::Vec3d& pos) const {
    pos = vertices[faces[n][v]];
  }
};

class ComChibifireSceneOptimize : public godot::Reference {
private:
	GODOT_CLASS(ComChibifireSceneOptimize, Reference);
public:
	ComChibifireSceneOptimize() {
		 MeshDataAdapter mesh;
	}
	static void _register_methods() {}
};
