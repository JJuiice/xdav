// Copyright (c) 2021 Ojas Anand.
//
// This file is part of xdav. xdav is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version. GNU package is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of
// the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.


#include "io.h"
#include <iostream>

std::string validateInputFile(int args, const char *filepath)
{
	if (args != 2) {
		std::fprintf(stderr, "Must provide input file location\n");
		return "";
	}

	std::string fp(filepath);

	if (fp.find("wav", fp.length() - 3) == std::string::npos) {
		std::fprintf(stderr, "Input file must be a WAV file\n");
		return "";
	}

#ifdef _WIN32 
	const char DELIMITER = '\\';
#else
	const char DELIMITER = '/';
#endif

	const int LAST_DELIMITER_INX = fp.find_last_of(DELIMITER) + 1;

	return fp.substr(LAST_DELIMITER_INX, (fp.length() - 4) - LAST_DELIMITER_INX);
}

int main(int argc, char *argv[])
{
	std::string title = validateInputFile(argc, argv[1]);

	if (!title.empty()) {
		AudioIO	audio;
		// VideoIO window(title);
		
		return audio.loadWAVFile(argv[1]);// window.openWindow();
	}

	return -1;
}
