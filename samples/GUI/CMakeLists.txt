project("GUI")

cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_executable(GUI-Executable
    src/main.cpp
    src/GUIMainMenu.cpp)

include_directories(/usr/include/freetype2
    "../../sunglasses/include")

#find_library(SUNGLASSES_LIB
#    sunglasses
#    "../../sunglasses/")

target_link_libraries(GUI-Executable sunglasses freetype SOIL GLEW GL assimp openal alut ${GLFW_LIBRARIES} X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua)
set(CMAKE_CXX_FLAGS "-std=c++14 -g")
