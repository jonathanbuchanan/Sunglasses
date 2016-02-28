project("Feature")

cmake_minimum_required(VERSION 3.2)

file(GLOB SOURCES Source/*.cpp)

add_executable(Feature-Executable ${SOURCES})

include_directories(/usr/include/freetype2)

add_definitions(-DLUA_COMPAT_5_2)
target_link_libraries(Feature-Executable sunglasses freetype SOIL GLEW libGL.so assimp sfml-audio glfw X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
