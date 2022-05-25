cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(cartesian-plotter VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(External)

find_package(GLEW REQUIRED)

file(GLOB_RECURSE
	SRC ./Source/*.cpp
)

add_executable(${PROJECT_NAME} Main.cpp ${SRC})

target_include_directories(${PROJECT_NAME}
    PRIVATE "${GLEW_INCLUDE_DIRS}"
    ./Source/
)

target_link_libraries(${PROJECT_NAME}
    IMGUI
    glfw
    GLEW::GLEW
    glm::glm
    GL
)

target_precompile_headers(${PROJECT_NAME}
    PRIVATE ./Source/PCH.h
)