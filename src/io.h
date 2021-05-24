// Copyright (c) 2021 Ojas Anand.
//
// This file is part of xdav. xdav is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version. GNU package is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of
// the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.


#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <stdint.h>

#include "soloud.h"

typedef struct WAV_HEADER {
	char		riffID[4];
	uint32_t    riffSize;
	char		riffFType[4];
	char		fmtID[4];
	uint32_t	fmtSize;
	uint16_t    aFmt;
	uint16_t	numChans;
	uint32_t	sRate;
	uint32_t	byRate;
	uint16_t	blAlign;
	uint16_t	bps;
	char    	dataID[4];
	uint32_t	dataSize;
} WAVHeader;

class AudioIO
{
private:
	WAVHeader wh;
	std::vector<char> wd;
	SoLoud::Soloud soloud;
	void readChar(std::ifstream &aFile, char (&buffer)[4]);
	uint16_t read16(std::ifstream &aFile);
	uint32_t read32(std::ifstream &aFile);
public:
	AudioIO();
	~AudioIO();
	int loadWAVFile(const char* fp);
	int streamAudioData();
};

class VideoIO
{
private:
	std::string m_title;
public:
	VideoIO(std::string title);
	int openWindow();
};

#endif
