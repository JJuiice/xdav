// Copyright (c) 2021 Ojas Anand.
//
// This file is part of xdimav. xdimav is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version. GNU package is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of
// the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.


#include "io.h"
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

void errCB(int error, const char* description)
{
	std::fprintf(stderr, "Error #%d: %s\n", error, description);
}

VideoIO::VideoIO()
{
}

int VideoIO::openWindow()
{
	int ret = 0;

	// Initialize GLFW
	if (glfwInit()) {
		glfwSetErrorCallback(errCB);

		// Set up context
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		GLFWwindow* window = glfwCreateWindow(640, 640, "xdimav", NULL, NULL);

		if (window) {
			glfwMakeContextCurrent(window);
			glfwSwapInterval(1);
			gladLoadGL(glfwGetProcAddress);

			while (!glfwWindowShouldClose(window)) {
				glClear(GL_COLOR_BUFFER_BIT);
				glfwSwapBuffers(window);
				glfwPollEvents();
			}

			glfwDestroyWindow(window);
		}
		else {
			ret = -1;
		}
	}
	else {
		ret = -1;
	}

	glfwTerminate();
	return ret;
}
