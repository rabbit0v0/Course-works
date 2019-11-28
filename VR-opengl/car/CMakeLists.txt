cmake_minimum_required(VERSION 3.7)
project(OpenGL3)

set(CMAKE_CXX_STANDARD 11)

set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
set(GLM_H /usr/local/Cellar/glm/0.9.9.2/include/glm)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
include_directories(${GLEW_H} ${GLFW_H} ${GLAD_H} ${KH_H} ${GLM_H})

find_library(OPENGL OpenGL)

set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

set(SOURCE_FILES main.cpp ${Util_Dir}glad.c)
add_executable(OpenGL3 ${SOURCE_FILES})

target_link_libraries(OpenGL3 "-framework OpenGL")