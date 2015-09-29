cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project("SEngineX")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
	set(GLFW_LOCATION "${CMAKE_SOURCE_DIR}/Dependencies/glfw-3.1.1.bin.WIN64")
	set(ASSIMP_LOCATION "${CMAKE_SOURCE_DIR}/Dependencies/assimp-3.1.1-win-binaries")
	SET( ENV{FREETYPE_DIR} "${CMAKE_SOURCE_DIR}/Dependencies/Freetype")
	set(GLEW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/glew-1.13.0/include")
	set(GLEW_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Dependencies/glew-1.13.0/lib/Release/x64")
	set(FREEIMAGE_ROOT "${CMAKE_SOURCE_DIR}/Dependencies/FreeImage/Dist/x64")
	set(RAPIDJSON_INCLUDEDIR "${CMAKE_SOURCE_DIR}/Dependencies/rapidjson")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(WIN32)

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

find_package(GLFW REQUIRED)
message(STATUS "Found GLFW in ${GLFW_LIBRARIES}")
include_directories(${GLFW_INCLUDE_DIR})
set(LIBS ${GLFW_LIBRARIES})

find_package(ASSIMP REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIR})
set(LIBS ${LIBS} ${ASSIMP_LIBRARIES})

find_package(FreeImage REQUIRED)
include_directories(${FREEIMAGE_INCLUDE_DIRS})
set(LIBS ${LIBS} ${FREEIMAGE_LIBRARIES})

find_package(FreeType REQUIRED)
message(STATUS "Found FreeType in ${FREETYPE_LIBRARIES}")
include_directories(${FREETYPE_INCLUDE_DIRS})
set(LIBS ${LIBS} ${FREETYPE_LIBRARIES})

find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL in ${OPENGL_LIBRARIES}")
include_directories(${OPENGL_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OPENGL_LIBRARIES})

if(WIN32)
	find_library(GLEW_LIBRARIES NAMES GLEW glew32 glew glew32s HINTS "${GLEW_LIBRARY_DIR}" PATH_SUFFIXES lib64)
else()
	find_package(GLEW REQUIRED)
endif(WIN32)

message(STATUS "Found GLEW in ${GLEW_LIBRARIES}")
include_directories(${GLEW_INCLUDE_DIR})
set(LIBS ${LIBS} ${GLEW_LIBRARIES})

find_package(RapidJSON REQUIRED)
include_directories(${RAPIDJSON_INCLUDE_DIRS})

add_subdirectory(SEngineX)

add_executable(demo main.cpp)
target_link_libraries(demo engine ${LIBS})

file(COPY Resources DESTINATION ${PROJECT_BINARY_DIR})