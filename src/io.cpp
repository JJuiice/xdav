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

#define WAV_HEADER_BYTE_SIZE 44

void errCB(int error, const char* description)
{
	std::fprintf(stderr, "Error #%d: %s\n", error, description);
}

AudioIO::AudioIO() : wh({})
{
}

int AudioIO::readAudioStream(char *buffer, int bytes, std::ifstream &aFile)
{
	if (!aFile.read(buffer, bytes)) {
		std::fprintf(stderr, "Error parsing audio file. Read %" PRIu64 " bytes when %d were expected.\n", aFile.gcount(), bytes);
		aFile.clear();
		return -1;
	}

	return 0;
}

void AudioIO::readChar(char* buffer, int* offset, char (&val)[4])
{
	std::copy(buffer + *offset, buffer + *offset + 4, val);
	*offset += 4;
}

/**
* Reads 16-bit unsigned integer from buffer
* @param buffer the binary data buffer
* @param offset the buffer offset
* @return UINT16
*/
uint16_t AudioIO::read16(char* buffer, int* offset)
{
	uint16_t val = (buffer[*offset + 1] << 8 | buffer[*offset]);
	*offset += 2;
	return val;
}

/**
* Reads 32-bit unsigned integer from buffer
* @param buffer the binary data buffer
* @param offset the buffer offset
* @return UINT32
*/
uint32_t AudioIO::read32(char* buffer, int* offset)
{
	uint16_t lsb = read16(buffer, offset);
	uint16_t msb = read16(buffer, offset);
	return (msb << 16 | lsb);
}

/**
* Load WAV file into memory
* @param fp filepath string
*/
int AudioIO::loadWAVFile(const char* fp)
{
	// Open audio file stream and prepare to read
	std::ifstream aFile(fp, std::ios::in | std::ios::binary);
	char headerBuffer[WAV_HEADER_BYTE_SIZE];
	int offset = 0;

	// Read Header into Memory
	if (readAudioStream(headerBuffer, WAV_HEADER_BYTE_SIZE, aFile))
		return -1;

	// Parse Header
	readChar(headerBuffer, &offset, wh.riffID);
	wh.riffSize = read32(headerBuffer, &offset);
	readChar(headerBuffer, &offset, wh.riffFType);
	readChar(headerBuffer, &offset, wh.fmtID);
	wh.fmtSize = read32(headerBuffer, &offset);
	wh.aFmt = read16(headerBuffer, &offset);
	wh.numChans = read16(headerBuffer, &offset);
	wh.sRate = read32(headerBuffer, &offset);
	wh.byRate = read32(headerBuffer, &offset);
	wh.blAlign = read16(headerBuffer, &offset);
	wh.bps = read16(headerBuffer, &offset);
	readChar(headerBuffer, &offset, wh.dataID);
	wh.dataSize = read32(headerBuffer, &offset);
	
	// Load WAV Data Into Memory
	char *dataBuffer = (char *) std::malloc(wh.dataSize * sizeof(char));
	if (readAudioStream(dataBuffer, wh.dataSize, aFile))
		return -1;

	// Load WAV Data Buffer Into Object Vector
	wd.insert(wd.begin(), dataBuffer, (dataBuffer+wh.dataSize));

	// Free WAV Data Buffer
	std::free(dataBuffer);
	dataBuffer = NULL;

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
		glfwSetErrorCallback(errCB);

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
