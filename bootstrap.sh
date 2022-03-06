export EmscriptenRoot=~/emsdk
rm -rf build
mkdir build
cd build
cmake .. -G "Unix Makefiles" \
	-DCMAKE_TOOLCHAIN_FILE=$EmscriptenRoot/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake \
	-DCMAKE_BUILD_TYPE=Debug
cd ..
