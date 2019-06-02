# Godot Fbx importer

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
./vcpkg install boost zlib blosc openexr tbb
./vcpkg integrate install
```

Building OpenVDB

```
cd src/thirdparty/openvdb
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=c:\tools\vcpkg\scripts\buildsystems\vcpkg.cmake ..
make -j4
make install
```
