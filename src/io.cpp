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
#include <inttypes.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

void OpenGLErrCB(int error, const char* description)
{
	std::fprintf(stderr, "Error #%d: %s\n", error, description);
}

AudioIO::AudioIO() : wh({})
{
}

void AudioIO::readChar(std::ifstream &aFile, char (&buffer)[4])
{
	aFile.read(buffer, sizeof(char) * 4);
}

/**
* Reads 16-bit unsigned integer from buffer
* @param buffer the binary data buffer
* @param offset the buffer offset
* @return UINT16
*/
uint16_t AudioIO::read16(std::ifstream &aFile)
{
	uint16_t val; 
	aFile.read(reinterpret_cast<char*>(&val), sizeof(uint16_t));
	return val;
}

/**
* Reads 32-bit unsigned integer from buffer
* @param buffer the binary data buffer
* @param offset the buffer offset
* @return UINT32
*/
uint32_t AudioIO::read32(std::ifstream &aFile)
{
	uint32_t val;
	aFile.read(reinterpret_cast<char*>(&val), sizeof(uint32_t));
	return val;
}

/**
* Load WAV file into memory
* @param fp filepath string
*/
int AudioIO::loadWAVFile(const char* fp)
{
	// Open audio file stream and prepare to read
	std::ifstream aFile(fp, std::ios::in | std::ios::binary);
	aFile.exceptions(std::ios::failbit | std::ios::badbit);

	try {
		// Parse Header
		readChar(aFile, wh.riffID);
		wh.riffSize = read32(aFile);
		readChar(aFile, wh.riffFType);
		readChar(aFile, wh.fmtID);
		wh.fmtSize = read32(aFile);
		wh.aFmt = read16(aFile);
		wh.numChans = read16(aFile);
		wh.sRate = read32(aFile);
		wh.byRate = read32(aFile);
		wh.blAlign = read16(aFile);
		wh.bps = read16(aFile);
		readChar(aFile, wh.dataID);
		wh.dataSize = read32(aFile);

		// Load WAV Data Into Memory
		char* dataBuffer = (char*)std::malloc(wh.dataSize * sizeof(char));
		aFile.read(dataBuffer, wh.dataSize);

		// Load WAV Data Buffer Into Object Vector
		wd.insert(wd.begin(), dataBuffer, (dataBuffer + wh.dataSize));

		// Free WAV Data Buffer
		std::free(dataBuffer);
		dataBuffer = NULL;
	}
	catch (std::ifstream::failure e) {
		std::cerr << "File stream failure: " << e.what() << std::endl
				  << "Error code: " << e.code() << std::endl;
		aFile.clear();
		return -1;
	}

	return 0;
}

VideoIO::VideoIO(std::string title) : 
	m_title(title)
{
}

/**
* Open OpenGL window and set current context
* @return 0 if there is no error, 1 if there is
*/
int VideoIO::openWindow()
{
	int noErr = glfwInit();

	// Initialize GLFW
	if (noErr) {
		glfwSetErrorCallback(OpenGLErrCB);

		// Set up context
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		GLFWwindow* window = glfwCreateWindow(640, 640, m_title.c_str(), NULL, NULL);

		noErr = !window;
		if (window) {
			// Set current context to the instantiated window and GL parameters
			glfwMakeContextCurrent(window);
			glfwSwapInterval(1);
			gladLoadGL(glfwGetProcAddress);

			// Keep window open while close event hasn't been sent
			while (!glfwWindowShouldClose(window)) {
				glClear(GL_COLOR_BUFFER_BIT);
				glfwSwapBuffers(window);
				glfwPollEvents();
			}

			// Destroy window
			glfwDestroyWindow(window);
		}
	}

	glfwTerminate();
	return (!noErr);
}
