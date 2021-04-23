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

typedef struct WAV_HEADER {
	char		riffID[4];
	uint32_t    riffSize;
	char		riffFType[4];
	char		fmtID[4];
	uint32_t	fmtSize;
	uint16_t    aFmt;
	uint16_t	numChans;
	uint32_t	sRate;
	uint32_t	bRate;
	uint16_t	blAlign;
	uint16_t	bps;
	char    	dataID[4];
	uint32_t	dataSize;
} WAVHeader;

void errCB(int error, const char* description)
{
	std::fprintf(stderr, "Error #%d: %s\n", error, description);
}

AudioIO::AudioIO(const char* fp) : 
	m_aFile(fp, std::ios::in | std::ios::binary)
{
}

int AudioIO::readFileBytes(char (&buffer)[4])
{
	if (!m_aFile.read(buffer, 4)) {
		std::fprintf(stderr, "Error parsing audio file. Read %" PRIu64 " bytes when %d were expected.\n", m_aFile.gcount(), 4);
		m_aFile.clear();
		return -1;
	}

	return 0;
}

int AudioIO::readFileBytes(uint32_t* val)
{
	char buffer[4];
	if (!m_aFile.read(buffer, 4)) {
		std::fprintf(stderr, "Error parsing audio file. Read %" PRIu64 " bytes when %d were expected.\n", m_aFile.gcount(), 4);
		m_aFile.clear();
		return -1;
	}

	std::copy(std::begin(buffer), std::end(buffer), val);
	return 0;

}

int AudioIO::readFileBytes(uint16_t *val)
{
	char buffer[2];
	if (!m_aFile.read(buffer, 2)) {
		std::fprintf(stderr, "Error parsing audio file. Read %" PRIu64 " bytes when %d were expected.\n", m_aFile.gcount(), 2);
		m_aFile.clear();
		return -1;
	}

	std::copy(std::begin(buffer), std::end(buffer), val);
	return 0;
}

int AudioIO::parseWAVFile()
{
	WAVHeader wh;

	if (readFileBytes(wh.riffID))
		return -1;

	if (readFileBytes(&(wh.riffSize)))
		return -1;

	if (readFileBytes(wh.riffFType))
		return -1;

	if (readFileBytes(wh.fmtID))
		return -1;

	if (readFileBytes(&(wh.fmtSize)))
		return -1;

	if (readFileBytes(&(wh.aFmt)))
		return -1;

	if (readFileBytes(&(wh.numChans)))
		return -1;

	if (readFileBytes(&(wh.sRate)))
		return -1;

	if (readFileBytes(&(wh.sRate)))
		return -1;

	if (readFileBytes(&(wh.bRate)))
		return -1;

	if (readFileBytes(&(wh.blAlign)))
		return -1;

	if (readFileBytes(&(wh.bps)))
		return -1;

	if (readFileBytes(wh.dataID))
		return -1;

	if (readFileBytes(&(wh.dataSize)))
		return -1;

	return 0;
}

VideoIO::VideoIO(std::string title) : 
	m_title(title)
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
		GLFWwindow* window = glfwCreateWindow(640, 640, m_title.c_str(), NULL, NULL);

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
