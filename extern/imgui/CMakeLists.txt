#imgui 
add_library(imgui INTERFACE)
target_include_directories(imgui INTERFACE
 .
 ./backends
 )
file(GLOB IMGUI_FILES 
    ./*.h 
    ./*.cpp 
    ./backends/imgui_impl_opengl3.*
    ./backends/imgui_impl_glfw.*
    ./backends/imgui_impl_opengl3_loader.h
)
target_sources(imgui INTERFACE ${IMGUI_FILES})
target_link_libraries(imgui INTERFACE  glfw OpenGL::GL)


add_executable(imgui_example ./examples/example_glfw_opengl3/main.cpp)
target_link_libraries(imgui_example PRIVATE imgui glfw)