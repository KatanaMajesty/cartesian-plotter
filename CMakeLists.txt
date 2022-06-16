cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(cartesian-plotter VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(External)

find_package(GLEW REQUIRED)

file(GLOB_RECURSE SRC ./Source/*.cpp)
# file(GLOB_RECURSE INL ./Source/Utility/Matrix.inl)

add_executable(${PROJECT_NAME} Main.cpp ${SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME}
    PRIVATE "${GLEW_INCLUDE_DIRS}"
    ./Source/
)

target_link_libraries(${PROJECT_NAME}
    IMGUI
    glfw
    GLEW::GLEW
    GL
)

target_precompile_headers(${PROJECT_NAME}
    PRIVATE ./Source/PCH.h
)