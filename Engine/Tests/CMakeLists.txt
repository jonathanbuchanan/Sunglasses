cmake_minimum_required(VERSION 2.8)
include(ExternalProject)




externalproject_add(gtest
    URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    INSTALL_COMMAND "")
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)
externalproject_get_property(gtest source_dir binary_dir)
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")
include_directories("${source_dir}/include")
set(GTEST_LIBRARY "${binary_dir}/libgtest.a")




externalproject_add(gmock
    URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gmock
    INSTALL_COMMAND "")
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gmock)
externalproject_get_property(gmock source_dir binary_dir)
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}")
include_directories("${source_dir}/include")
set(GMOCK_LIBRARY "${binary_dir}/libgmock.a")




project(Test-Sunglasses)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Test-Sunglasses ${SOURCES})
include_directories(/usr/include/freetype2)
target_link_libraries(Test-Sunglasses sunglasses lua ${GTEST_LIBRARY} ${GMOCK_LIBRARY} pthread)
add_dependencies(Test-Sunglasses gtest)
add_dependencies(Test-Sunglasses gmock)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wpedantic -g")
