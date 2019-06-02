# Godot Scene Optimize

A openvdb plugin for Godot Engine 3.2 master.

## Dependencies

```
> git clone https://github.com/Microsoft/vcpkg.git
> cd vcpkg

PS> .\bootstrap-vcpkg.bat
```

Windows
Installing Dependencies (Boost, TBB, OpenEXR, Blosc)

```
./vcpkg install boost zlib blosc openexr tbb openvdb
./vcpkg integrate install
```

Building OpenVDB

```
cd src/thirdparty/openvdb
mkdir build
cd build
"c:\Program Files\CMake\bin\cmake.exe" -DCMAKE_TOOLCHAIN_FILE=c:\tools\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows ..\src\
make -j4
make install
```
