# Set up cmake to use Emscripten
#
# To set up emscripten:
#
# git clone https://github.com/emscripten-core/emsdk.git
# ./emsdk install latest
# ./emsdk activate latest
#
# On windows, it's best to use emsdk.ps1 from powershell
#
# Then set an environment variable EMSDK_ROOT to the root of the git repository.
#
# Cmake 3.22 is pre-installed for Visual Studio 2022 Cmake Tools
cmake_minimum_required(VERSION 3.22)

project(EmscriptenTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions("-std=c++20")

add_executable(client main.cpp)

set_target_properties(client PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 --bind")
