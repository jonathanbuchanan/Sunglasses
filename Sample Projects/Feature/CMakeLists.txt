project("Feature")

cmake_minimum_required(VERSION 3.2)

set(ENGINE_PATH ../../Engine/Runtime)

file(GLOB SOURCES /Source/*.cpp)
file(GLOB_RECURSE ENGINE_SOURCE "${ENGINE_PATH}/*.cpp")

add_executable(Feature ${SOURCES} ${ENGINE_SOURCE})

include_directories(${CMAKE_SOURCE_DIR}/../../Engine/Runtime /usr/include/freetype2)

target_link_libraries(Feature freetype SOIL GLEW libGL.so assimp sfml-audio glfw3 X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
