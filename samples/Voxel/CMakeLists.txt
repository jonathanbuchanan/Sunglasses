project("Voxel")

cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories("/usr/local/include/freetype2"
    "../../sunglasses/include/"
    "/usr/local/include/")

include_directories("/usr/include/freetype2/"
    "/usr/local/include/"
    "include/")
link_directories("/usr/local/lib/")

add_executable(Voxel-Executable src/main.cpp src/MainMenu.cpp src/OptionsMenu.cpp)

find_package(PkgConfig)
pkg_search_module(FT2 REQUIRED freetype2)
set(CMAKE_CXX_FLAGS "${FT2_CFLAGS} -std=c++14 -g -Wall -Wextra")

find_library(SOIL_LIB SOIL)


if (UNIX AND NOT APPLE)
target_link_libraries(Voxel-Executable sunglasses freetype ${SOIL_LIB} libGL.so GLEW assimp openal alut glfw3 X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua)
elseif (APPLE)
find_library(GL_LIB OpenGL)
target_link_libraries(Voxel-Executable sunglasses freetype ${SOIL_LIB} GLEW ${GL_LIB} assimp openal alut glfw3 pthread dl lua)
endif()