project("Sunglasses")

cmake_minimum_required(VERSION 3.2)

file(GLOB_RECURSE SOURCES "Runtime/*.cpp")

add_library(sunglasses SHARED ${SOURCES})
target_link_libraries(sunglasses freetype SOIL GLEW libGL.so assimp sfml-audio glfw X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua)
install(TARGETS sunglasses LIBRARY DESTINATION lib)

add_library(sunglasses-static STATIC ${SOURCES})
target_link_libraries(sunglasses-static freetype SOIL GLEW libGL.so assimp sfml-audio glfw X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua)

include_directories(${CMAKE_SOURCE_DIR}/Runtime/Core ${CMAKE_SOURCE_DIR}/Runtime /usr/include/freetype2)

add_definitions(-DLUA_COMPAT_5_2)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
