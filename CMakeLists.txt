cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/thirdparty/openvdb/cmake)
project(com_chibifire_openvdb VERSION 0.0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(DEBUG_ENABLED DEBUG_ENABLED DEBUG_MEMORY_ENABLED)
set(TOOLS_ENABLED TOOLS_ENABLED)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sample/addons/com_chibifire_openvdb/bin/osx.64)

add_library(com_chibifire_openvdb
            SHARED
        "sample/addons/com_chibifire_scene_optimize/src/Godot.cpp"
        "sample/addons/com_chibifire_scene_optimize/src/ComChibifireSceneOptimize.h"
        "sample/addons/com_chibifire_scene_optimize/src/ComChibifireSceneOptimize.cpp"
        "thirdparty/godot-cpp/godot_headers/gdnative/gdnative.h"
        "thirdparty/godot-cpp/godot_headers/nativescript/godot_nativescript.h"
)

target_include_directories(com_chibifire_openvdb
                            PUBLIC
                            "thirdparty/godot-cpp/include"
                             "thirdparty/godot-cpp/include/gen"
                            "thirdparty/godot-cpp/godot_headers"
                            /usr/local/Cellar/openvdb/6.1.0/include/
                            "thirdparty/godot/modules/gdnative/include"
                            "thirdparty/godot-cpp/include"
                            "thirdparty/godot-cpp/include/gen"
                            "thirdparty/godot-cpp/godot_headers"
                            "thirdparty/godot-cpp/include/core")

if(APPLE)
target_link_libraries(com_chibifire_openvdb 
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/godot-cpp/bin/libgodot-cpp.osx.release.64.a
"-framework Cocoa")
elseif(MSVC)
target_link_libraries(com_chibifire_openvdb
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/godot-cpp/bin/libgodot-cpp.windows.release.64.lib)
else(UNIX)
target_link_libraries(com_chibifire_openvdb
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/godot-cpp/bin/libgodot-cpp.linux.release.64.a)
endif()

file(COPY sample DESTINATION .)