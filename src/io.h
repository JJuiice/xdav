// Copyright (c) 2021 Ojas Anand.
//
// This file is part of xdimav. xdimav is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version. GNU package is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of
// the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.


#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <string>
#include <fstream>
#include <stdint.h>

class AudioIO
{
private:
	std::ifstream m_aFile;
	int readFileBytes(char (&buffer)[4]);
	int readFileBytes(uint32_t* val);
	int readFileBytes(uint16_t *val);
public:
	AudioIO(const char *fp);
	int parseWAVFile();
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
