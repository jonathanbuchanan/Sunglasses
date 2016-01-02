project("Feature")

cmake_minimum_required(VERSION 3.2)

file(GLOB SOURCES Source/*.cpp)

add_executable(Feature ${SOURCES})

target_link_libraries(Feature)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
