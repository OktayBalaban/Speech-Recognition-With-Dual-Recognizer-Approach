#pragma once
#include "Recognizer.h"
#include "VoiceInputTaker.h"

#include <iostream>
#include <string>
#include <chrono>
#include <thread>



class MainManager
{
public:
	void Init();

private:

	Recognizer mRecognizer;
	VoiceInputTaker mVoiceInputTaker;

	bool mIsRunning;
	bool mIsStartRecognizing;

	void run();
};

