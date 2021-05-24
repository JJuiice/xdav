# Copyright (c) 2021 Ojas Anand.
#
# This file is part of xdav. xdav is free software: you can redistribute it and/or modify it under the
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
find_library(GLFW3_LIB NAMES glfw3 HINTS "${DEPS}/GLFW/lib")

# Add source to this project's executable.
set(SRCS
		"main.cpp"
		"io.cpp"
		"io.h"
		"fft.cpp"
		"fft.h")
add_executable (xdav ${SRCS} ${GLAD_GL_SRC})

# Install targets
target_include_directories(xdav PRIVATE "${DEPS}/GLFW/include" "${DEPS}/GLAD/include" "${DEPS}/SoLoud/include")
target_link_libraries(xdav PRIVATE ${GLFW3_LIB} ${OPENAL_LIB})
