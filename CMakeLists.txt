cmake_minimum_required(VERSION 3.5)

project(com_chibifire_openvdb VERSION 0.0.1 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(DEBUG_ENABLED DEBUG_ENABLED DEBUG_MEMORY_ENABLED)
set(TOOLS_ENABLED TOOLS_ENABLED)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sample/addons/com_chibifire_openvdb/bin/windows.64)
find_package(OpenVDB REQUIRED)
target_include_directories(com_chibifire_openvdb
                            PUBLIC)

if(OSX)
target_link_libraries(com_chibifire_openvdb OpenVDB::openvdb
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/godot-cpp/bin/libgodot-cpp.osx.release.64.a
"-framework Cocoa")
elseif(MSVC)
target_link_libraries(com_chibifire_openvdb OpenVDB::openvdb 
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/godot-cpp/bin/libgodot-cpp.windows.release.64.lib)
elseif(UNIX)
target_link_libraries(com_chibifire_openvdb OpenVDB::openvdb
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/godot-cpp/bin/libgodot-cpp.linux.release.64.a)
endif(OSX)

file(COPY sample DESTINATION .)