cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(miniGL CXX)

# set default build type to release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# 设置输出目录为build/bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_DEBUG_POSTFIX "_d")


add_executable(main
	  src/main.cpp
	  ${PROJECT_SOURCE_DIR}/extern/glfw/deps/glad_gl.c
	  ${PROJECT_SOURCE_DIR}/src/Visualization/MiniGL.cpp                       
	  ${PROJECT_SOURCE_DIR}/src/Visualization/Shader.cpp       
)

# -------------------------------------------------------------------------- #
#                           set external libraries                           #
# -------------------------------------------------------------------------- #
include_directories( ${PROJECT_SOURCE_DIR}/extern/eigen )
include_directories(${PROJECT_SOURCE_DIR}/extern/freeglut/include)
include_directories(${PROJECT_SOURCE_DIR}/extern/glew/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries(main glfw)
target_link_libraries(main OpenGL::GL)

set(EXTERN_DIR ${PROJECT_SOURCE_DIR}/extern)
# eigen
add_library(Eigen INTERFACE)
target_include_directories(Eigen INTERFACE ${EXTERN_DIR}/eigen)
# opengl
find_package(OpenGL REQUIRED) # windows SDK中有opengl的库
# glfw
add_subdirectory(extern/glfw)
#imgui 
# add_subdirectory(extern/imgui)



# target_link_libraries(main PRIVATE
#     OpenGL::GL
#     glad
#     glfw
#     glm
#     Eigen
#     imgui
# )
