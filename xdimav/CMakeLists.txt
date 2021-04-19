# CMakeList.txt : CMake project for xdimav, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Dependencies directory
set(DEPS "${CMAKE_SOURCE_DIR}/Dependencies")
set(GLAD_GL_SRC "${CMAKE_SOURCE_DIR}/Dependencies/GLAD/src/gl.c")

# Required libraries
find_library(GLFW3_LIB NAMES glfw3 HINTS "${DEPS}/GLFW/lib-vc2019")

# Add source to this project's executable.
add_executable (xdimav "xdimav.cpp" ${GLAD_GL_SRC})

# Install targets
target_include_directories(xdimav PRIVATE "${DEPS}/GLFW/include")
target_include_directories(xdimav PRIVATE "${DEPS}/GLAD/include")
target_link_libraries(xdimav PRIVATE ${GLFW3_LIB})
