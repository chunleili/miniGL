cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(miniGL CXX)

# set default build type to release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# set output dir as build/bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_DEBUG_POSTFIX "_d")

# main executable
add_executable(main
	  src/main.cpp
	  ${PROJECT_SOURCE_DIR}/extern/glfw/deps/glad_gl.c
	  ${PROJECT_SOURCE_DIR}/src/Visualization/MiniGL.cpp                       
	  ${PROJECT_SOURCE_DIR}/src/Visualization/Shader.cpp       
)

include_directories(${PROJECT_SOURCE_DIR}/src)
# -------------------------------------------------------------------------- #
#                           set external libraries                           #
# -------------------------------------------------------------------------- #

# eigen
include_directories( ${PROJECT_SOURCE_DIR}/extern/eigen )
# opengl
find_package(OpenGL REQUIRED) # windows SDK中有opengl的库
target_link_libraries(main OpenGL::GL)
# glfw
add_subdirectory(extern/glfw)
target_link_libraries(main glfw)
