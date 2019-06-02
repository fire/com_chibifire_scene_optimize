cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/thirdparty/openvdb/cmake)
project(com_chibifire_scene_optimize VERSION 0.0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(DEBUG_ENABLED DEBUG_ENABLED DEBUG_MEMORY_ENABLED)
set(TOOLS_ENABLED TOOLS_ENABLED)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_definitions(NOMINMAX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sample/addons/com_chibifire_scene_optimize/bin/osx.64)
add_library(com_chibifire_scene_optimize
            SHARED
        "sample/addons/com_chibifire_scene_optimize/src/Godot.cpp"
        "sample/addons/com_chibifire_scene_optimize/src/ComChibifireSceneOptimize.h"
        "sample/addons/com_chibifire_scene_optimize/src/ComChibifireSceneOptimize.cpp"
        "thirdparty/godot-cpp/godot_headers/gdnative/gdnative.h"
        "thirdparty/godot-cpp/godot_headers/nativescript/godot_nativescript.h"
)

target_include_directories(com_chibifire_scene_optimize
                            PUBLIC
                            "thirdparty/godot-cpp/include"
                             "thirdparty/godot-cpp/include/gen"
                            "thirdparty/godot-cpp/godot_headers"
                            "thirdparty/godot/modules/gdnative/include"
                            "thirdparty/godot-cpp/include"
                            "thirdparty/godot-cpp/include/gen"
                            "thirdparty/godot-cpp/godot_headers"
                            "thirdparty/godot-cpp/include/core"
                            "thirdparty/openvdb/openvdb/tools"   
                            C:/tools/vcpkg/installed/x64-windows/include
                            /usr/local/Cellar/openvdb/6.1.0/include/
                            /usr/local/include)

if(APPLE)
target_link_libraries(com_chibifire_scene_optimize 
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/godot-cpp/bin/libgodot-cpp.osx.release.64.a
/usr/local/Cellar/openvdb/6.1.0/lib/libopenvdb.dylib
/usr/local/opt/tbb/lib/libtbb.dylib
/usr/local/opt/ilmbase/lib/libHalf.dylib
"-framework Cocoa")
set_target_properties(com_chibifire_scene_optimize
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/sample/addons/com_chibifire_scene_optimize/lib/mac/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/sample/addons/com_chibifire_scene_optimize/lib/mac/"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/sample/addons/com_chibifire_scene_optimize/lib/mac/"
)
elseif(MSVC)
target_link_libraries(com_chibifire_scene_optimize
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/godot-cpp/bin/libgodot-cpp.windows.release.default
"C:/tools/vcpkg/installed/x64-windows/lib/openvdb.lib"
"C:/tools/vcpkg/installed/x64-windows/lib/tbb.lib"
"C:/tools/vcpkg/installed/x64-windows/lib/Half-2_3_s.lib")
set_target_properties(com_chibifire_scene_optimize
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/sample/addons/com_chibifire_scene_optimize/lib/win/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/sample/addons/com_chibifire_scene_optimize/lib/win/"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/sample/addons/com_chibifire_scene_optimize/lib/win/"
)
else(UNIX)
target_link_libraries(com_chibifire_scene_optimize
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/godot-cpp/bin/libgodot-cpp.linux.release.64.a)
endif()

file(COPY sample DESTINATION .)
