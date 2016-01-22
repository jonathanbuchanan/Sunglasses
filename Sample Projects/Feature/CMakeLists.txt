project("Feature")

cmake_minimum_required(VERSION 3.2)

set(ENGINE_PATH ../../Engine/Runtime)

file(GLOB SOURCES Source/*.cpp)
file(GLOB_RECURSE ENGINE_SOURCE "${ENGINE_PATH}/*.cpp")

add_executable(Feature-Executable ${SOURCES} ${ENGINE_SOURCE})

include_directories(${CMAKE_SOURCE_DIR}/../../Engine/Runtime/Core ${CMAKE_SOURCE_DIR}/../../Engine/Runtime /usr/include/freetype2)

target_link_libraries(Feature-Executable freetype SOIL GLEW libGL.so assimp sfml-audio glfw X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
