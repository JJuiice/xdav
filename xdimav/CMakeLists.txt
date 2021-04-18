# CMakeList.txt : CMake project for xdimav, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories(${CMAKE_SOURCE_DIR}/Dependencies/GLFW)
link_directories(${CMAKE_SOURCE_DIR}/Dependences/lib-vc2019)

# Add source to this project's executable.
add_executable (xdimav "xdimav.cpp" "xdimav.h")
target_link_libraries(xdimav glfw3)

# TODO: Add tests and install targets if needed.
