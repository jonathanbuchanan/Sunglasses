project("Feature")

cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

file(GLOB SOURCES Source/*.cpp)

add_executable(Feature-Executable Source/FeatureGame.cpp Source/FeatureRenderer.cpp Source/FeatureScene.cpp Source/main.cpp)

include_directories(/usr/include/freetype2)

target_link_libraries(Feature-Executable sunglasses freetype SOIL GLEW libGL.so assimp sfml-audio ${GLFW_LIBRARIES} X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
