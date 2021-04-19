// Copyright (c) 2021 Ojas Anand.
//
// This file is part of xdimav. xdimav is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version. GNU package is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of
// the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.


#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

void errCB(int error, const char* description)
{
	std::fprintf(stderr, "Error #%d: %s\n", error, description);
}

int main()
{
	int ret = 0;
	std::string msg;
	
	// Initialize GLFW
	if (glfwInit()) {
		// Set up context
		glfwSetErrorCallback(errCB);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		GLFWwindow* window = glfwCreateWindow(640, 640, "xdimav", NULL, NULL);
		glfwMakeContextCurrent(window);
		gladLoadGL(glfwGetProcAddress);

		msg = "OpenGL Initialization Succeeded";

		while (!glfwWindowShouldClose(window));

		glfwDestroyWindow(window);
	}
	else {
		msg = "OpenGL Initialization Failed";
		ret = -1;
	}

	std::cout << msg << std::endl;

	glfwTerminate();
	return ret;
}
