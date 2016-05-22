project("Voxel")

cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_executable(Voxel-Executable src/main.cpp src/Game.cpp src/MenuScene.cpp src/GameScene.cpp
    src/World.cpp src/GameRenderer.cpp src/Chunk.cpp src/Block.cpp)

include_directories(/usr/include/freetype2)

target_link_libraries(Voxel-Executable sunglasses freetype SOIL GLEW libGL.so assimp openal alut ${GLFW_LIBRARIES} X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua)
set(CMAKE_CXX_FLAGS "-std=c++14 -g")
