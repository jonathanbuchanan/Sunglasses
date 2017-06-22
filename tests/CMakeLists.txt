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
    test_Node.cpp
    #test_Script.cpp
)

link_directories("/usr/local/lib/")

add_test(all Test-Sunglasses)

add_executable(Test-Sunglasses ${SOURCES})
include_directories(
    /usr/local/include/freetype2
    ../sunglasses/include/
    ../googletest/include/
    ../googlemock/include/
)

find_package(PkgConfig)
pkg_search_module(FT2 REQUIRED freetype2)
set(CMAKE_CXX_FLAGS "${FT2_CFLAGS} -std=c++14 -g -Wall -Wextra")

if (UNIX AND NOT APPLE)
target_link_libraries(Test-Sunglasses sunglasses freetype ${SOIL_LIB} libGL.so GLEW assimp openal alut glfw3 X11 Xxf86vm pthread dl Xrandr Xinerama Xi Xcursor lua gtest_main gmock_main pthread)
elseif (APPLE)
find_library(GL_LIB OpenGL)
target_link_libraries(Test-Sunglasses sunglasses freetype ${SOIL_LIB} GLEW ${GL_LIB} assimp openal alut glfw3 pthread dl lua gtest_main gmock_main pthread)
endif()

add_dependencies(Test-Sunglasses gtest)
add_dependencies(Test-Sunglasses gmock)
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Wpedantic -g")
