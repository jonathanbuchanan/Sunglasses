cmake_minimum_required(VERSION 2.8)
project(Test-Sunglasses)

# GMock already builds GTest, so no need to add it
add_subdirectory(googlemock)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Test-Sunglasses ${SOURCES})
include_directories(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include /usr/include/freetype2)
target_link_libraries(Test-Sunglasses sunglasses pthread lua gtest gmock)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wpedantic -g")
