cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(samples)

add_subdirectory(sunglasses)

enable_testing()

add_subdirectory(googlemock)
add_subdirectory(tests)
