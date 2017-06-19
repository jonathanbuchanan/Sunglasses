cmake_minimum_required(VERSION 3.2)

project("Sunglasses")

macro(add_sources)
    foreach(SRC ${ARGN})
        set(CAT_SRC "${CMAKE_CURRENT_SOURCE_DIR}/${SRC}")
        list(APPEND SRCS ${CAT_SRC})
    endforeach()
endmacro()

macro(add_sources_to_parent)
    set(SRCS ${SRCS} PARENT_SCOPE)
endmacro()

add_subdirectory(src)

include_directories("/usr/include/freetype2/"
    "/usr/local/include/"
    "include/")
link_directories("/usr/local/lib/")

add_library(sunglasses SHARED ${SRCS})

find_package(PkgConfig)
pkg_search_module(FT2 REQUIRED freetype2)
set(CMAKE_CXX_FLAGS "${FT2_CFLAGS} -std=c++14 -g -Wall -Wextra")

find_library(SOIL_LIB SOIL)


if (UNIX AND NOT APPLE)
target_link_libraries(sunglasses freetype ${SOIL_LIB} libGL.so GLEW assimp openal alut glfw3 X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua)
elseif (APPLE)
find_library(GL_LIB OpenGL)
target_link_libraries(sunglasses freetype ${SOIL_LIB} GLEW ${GL_LIB} assimp openal alut glfw3 pthread dl lua)
endif()

install(TARGETS sunglasses LIBRARY DESTINATION /usr/lib)

install(DIRECTORY ./
    DESTINATION include/sunglasses FILES_MATCHING
    PATTERN "CMakeFiles" EXCLUDE
    PATTERN "*.h"
    PATTERN "*.hpp")
