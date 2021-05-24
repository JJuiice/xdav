// Copyright (c) 2021 Ojas Anand.
//
// This file is part of xdav. xdav is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version. GNU package is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of
// the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.


#include "fft.h"

FFT::FFT()
{
}

/**
  * Convert time domain to frequency domain
  * @param domain Output array of frequency bins 
  * @param sRate Sample Rate (in Hz)
  * @param N Size of FFT
  * @return 0 on success; -1 on error 
  */
int FFT::secToFreq(double* domain, uint32_t sRate, unsigned short N)
{
	// TODO implement f = i * Fs / N
	// f: bin frequency, i: bin index
	// FFT size will be the size of the audio input stream
	// https://stackoverflow.com/a/4371627 for more info on what parts may be unnecessary (i.e. values above N/2)
	return 0;
}

/**
  * Perform FFT on audio data
  * @param audio Audio data to transform
  * @param size length of audio data
  * @return 0 on success; -1 on error
  */
int FFT::analyzeAudio(char* audio, unsigned int size)
{
	// TODO implement FFT
	// https://www.youtube.com/watch?v=EsJGuI7e_ZQ
	// https://towardsdatascience.com/understanding-audio-data-fourier-transform-fft-spectrogram-and-speech-recognition-a4072d228520
	return 0;
}
