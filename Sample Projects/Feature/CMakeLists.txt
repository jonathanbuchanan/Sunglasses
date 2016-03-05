project("Feature")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

cmake_minimum_required(VERSION 2.8)

set(ENGINE_PATH ../../Engine/Runtime)

file(GLOB SOURCES Source/*.cpp)
file(GLOB_RECURSE ENGINE_SOURCE "${ENGINE_PATH}/*.cpp")

add_executable(Feature-Executable Source/FeatureGame.cpp Source/FeatureRenderer.cpp Source/FeatureScene.cpp Source/main.cpp ${ENGINE_SOURCE})

include_directories(${CMAKE_SOURCE_DIR}/../../Engine/Runtime/Core ${CMAKE_SOURCE_DIR}/../../Engine/Runtime /usr/include/freetype2)

target_link_libraries(Feature-Executable freetype SOIL GLEW libGL.so assimp sfml-audio ${GLFW_LIBRARIES} X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
