cmake_minimum_required(VERSION 2.8)
include(ExternalProject)


find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)


project(Test-Sunglasses)

set(SOURCES
    main.cpp
    test_Action.cpp
    test_Base.cpp
    test_LuaPrimitives.cpp
    test_LuaTypeRegistrar.cpp
    test_ResourceManager.cpp
    test_ResourceService.cpp
    test_Script.cpp
)

add_test(all Test-Sunglasses)

add_executable(Test-Sunglasses ${SOURCES})
include_directories(
    /usr/include/freetype2
    ../sunglasses/include/
    ../googletest/include/
    ../googlemock/include/
)
target_link_libraries(Test-Sunglasses sunglasses freetype SOIL GLEW libGL.so assimp openal alut ${GLFW_LIBRARIES} X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua gtest_main gmock_main pthread)
add_dependencies(Test-Sunglasses gtest)
add_dependencies(Test-Sunglasses gmock)
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Wpedantic -g")
