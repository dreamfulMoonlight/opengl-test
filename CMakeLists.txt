cmake_minimum_required(VERSION 3.5)

project(opengl-test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON) #当前include 打开
include_directories(${PROJECT_BINARY_DIR}/include)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17) # C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_FOUND:= ${OPENGL_FOUND}")

if(OPENGL_FOUND)
    message('OPENGL_FOUND-is-true')
else()
    message('OPENGL_FOUND-is-false')
endif()

message(STATUS "OPENGL_INCLUDE_DIR:= ${OPENGL_INCLUDE_DIR}")
message(STATUS "OPENGL_LIBRARY:= ${OPENGL_LIBRARY}")
message(STATUS "OPENGL_LIBRARIES:= ${OPENGL_LIBRARIES}")

add_subdirectory(src)

target_include_directories(opengl-test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW
    ${CMAKE_CURRENT_SOURCE_DIR}/include/glew
    ${CMAKE_CURRENT_SOURCE_DIR}/include/opencv
    )

target_include_directories(opengl-test PUBLIC ${OPENGL_INCLUDE_DIR})