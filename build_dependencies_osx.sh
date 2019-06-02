#! /bin/bash
export current=`pwd`
export godot=`pwd`/thirdparty/godot
#cd $godot && scons p=osx target=release_debug -j`sysctl -n hw.ncpu` use_lto=no gdnative_wrapper=yes deprecated=no && cd $current && $godot/bin/godot.osx.opt.tools.64 --gdnative-generate-json-api thirdparty/godot-cpp/godot_api.json && cd thirdparty/godot-cpp/ && scons -j`sysctl -n hw.ncpu` godotbinpath="$godot/bin/godot.osx.opt.tools.64" headers="$godot/modules/gdnative/include" p=osx generate_bindings=yes target=release && cd $current

cd thirdparty/godot-cpp && scons -j`sysctl -n hw.ncpu` godotbinpath="$godot/bin/godot.osx.opt.tools.64" headers="$godot/modules/gdnative/include" p=osx generate_bindings=yes target=release && cd $current
