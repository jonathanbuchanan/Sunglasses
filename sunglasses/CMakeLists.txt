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

add_library(sunglasses SHARED ${SRCS})

include_directories("/usr/include/freetype2"
    "include/")

set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall -Wextra")

install(TARGETS sunglasses LIBRARY DESTINATION /usr/lib)

install(DIRECTORY ./
    DESTINATION include/sunglasses FILES_MATCHING
    PATTERN "CMakeFiles" EXCLUDE
    PATTERN "*.h"
    PATTERN "*.hpp")
