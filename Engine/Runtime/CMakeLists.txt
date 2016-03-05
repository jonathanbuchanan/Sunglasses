project("Sunglasses")

cmake_minimum_required(VERSION 3.2)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(CMAKE_INSTALL_PREFIX /usr)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(sunglasses SHARED ${SOURCES})
target_link_libraries(sunglasses freetype SOIL GLEW libGL.so assimp sfml-audio ${GLFW_LIBRARIES} X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua)
install(TARGETS sunglasses LIBRARY DESTINATION lib)

include_directories(/usr/include/freetype2)

add_definitions(-DLUA_COMPAT_5_2)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

install(DIRECTORY src/ DESTINATION include/Sunglasses FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
