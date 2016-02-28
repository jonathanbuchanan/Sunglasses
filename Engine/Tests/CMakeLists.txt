cmake_minimum_required(VERSION 2.8)
project(Test-Sunglasses)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Test-Sunglasses ${SOURCES})
include_directories(/usr/include/freetype2)
add_definitions(-DLUA_COMPAT_5_2)
target_link_libraries(Test-Sunglasses sunglasses pthread lua gtest gmock)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
