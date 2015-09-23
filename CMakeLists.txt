cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project("SEngineX")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

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
include_directories(${FREEIMAGE_INCLUDE_DIR})
set(LIBS ${LIBS} ${FREEIMAGE_LIBRARIES})

find_package(FreeType REQUIRED)
message(STATUS "Found FreeType in ${FREETYPE_LIBRARIES}")
include_directories(${FREETYPE_INCLUDE_DIRS})
set(LIBS ${LIBS} ${FREETYPE_LIBRARIES})

find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL in ${OPENGL_LIBRARIES}")
include_directories(${OPENGL_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)
message(STATUS "Found GLEW in ${GLEW_LIBRARIES}")
include_directories(${GLEW_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GLEW_LIBRARIES})

add_subdirectory(SEngineX)

add_executable(demo main.cpp)
target_link_libraries(demo engine ${LIBS})

file(COPY Resources DESTINATION ${PROJECT_BINARY_DIR})