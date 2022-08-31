set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(opengl-test main.cpp )

set(libpath "${PROJECT_SOURCE_DIR}/lib")


target_link_libraries(opengl-test PUBLIC
                        ${libpath}/GLFW/glfw3.lib
                        ${libpath}/glew/glew32.lib)


target_link_libraries(opengl-test PUBLIC ${OPENGL_LIBRARIES})

target_link_libraries(opengl-test PUBLIC
    $<$<CONFIG:Debug>:${PROJECT_SOURCE_DIR}/lib/opencv/debug/opencv_world453d.lib>
    $<$<CONFIG:Release>:${PROJECT_SOURCE_DIR}/lib/opencv/release/opencv_world453.lib>)
