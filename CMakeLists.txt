project("Sunglasses")

cmake_minimum_required(VERSION 3.2)

file(GLOB SOURCES *.cpp Graphics/*.cpp Graphics/GUI/*.cpp Graphics/Shaders/*.cpp Physics/*.cpp Audio/*.cpp)

add_executable(sunglasses ${SOURCES})
if (APPLE)
	add_definitions(-DRETINA)
ENDIF (APPLE)
target_link_libraries(sunglasses SOIL assimp freetype GLEW glfw3 sfml-audio libGL.so X11 Xrandr Xi Xinerama Xcursor Xxf86vm pthread dl)
include_directories(${CMAKE_SOURCE_DIR}/Libraries ${CMAKE_SOURCE_DIR}/Libraries/Freetype ${CMAKE_SOURCE_DIR}/Libraries/SOIL)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
