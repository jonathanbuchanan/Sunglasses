project("SunglassesEditor")

cmake_minimum_required(VERSION 3.2)

file(GLOB SOURCES *.cpp)

add_executable(SunglassesEditor ${SOURCES})
if (APPLE)
	add_definitions(-DRETINA)
ENDIF (APPLE)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

target_link_libraries(SunglassesEditor ${wxWidgets_LIBRARIES})
include_directories()
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
