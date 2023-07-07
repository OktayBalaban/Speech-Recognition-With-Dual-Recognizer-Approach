#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>

#include "vosk_api.h"
#include "al.h"
#include "alc.h"
#include "json.hpp"

class Recognizer
{
public:
	Recognizer();

	int Init(int sampleRate, std::string model);

	int Recognize(std::vector<ALCshort> &buffer, int sampleSize);


private:

	VoskRecognizer* mRecognizer1;
	VoskRecognizer* mRecognizer2;

	VoskModel* mModel;

	int mResultCounterThreshold;
	int mCounter1;
	int mCounter2;

	std::vector<std::string> parseResults(std::string results, float confidenceThreshold);
	int checkResults(std::vector<std::string> results);

	std::unordered_set<std::string> mAcceptedCommands;
};

