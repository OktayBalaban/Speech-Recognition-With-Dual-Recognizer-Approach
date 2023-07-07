#pragma once

#include <iostream>
#include <vector>

#include "al.h"
#include "alc.h"

class VoiceInputTaker
{
public:
	VoiceInputTaker();

	int Init(int sampleRate, int sampleSize);

	std::vector<ALCshort> GetInput();

private:

	int mSampleRate;
	int mSampleSize;

	ALCdevice* mDevice;

	void closeDevice();

	char* mBuffer;
};

