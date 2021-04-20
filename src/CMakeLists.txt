# Copyright (c) 2021 Ojas Anand.
#
# This file is part of xdimav. xdimav is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version. GNU package is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of
# the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.


cmake_minimum_required (VERSION 3.8)

# Dependencies directory
set(DEPS "${CMAKE_SOURCE_DIR}/deps")
set(GLAD_GL_SRC "${DEPS}/GLAD/src/gl.c")

# Required libraries
find_library(GLFW3_LIB NAMES glfw3 HINTS "${DEPS}/GLFW/lib-vc2019")

# Add source to this project's executable.
set(SRCS
		"main.cpp"
		"io.cpp"
		"io.h")
add_executable (xdimav ${SRCS} ${GLAD_GL_SRC})

# Install targets
target_include_directories(xdimav PRIVATE "${DEPS}/GLFW/include" "${DEPS}/GLAD/include")
target_link_libraries(xdimav PRIVATE ${GLFW3_LIB})
