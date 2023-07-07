#include "MainManager.h"

void MainManager::Init()
{
	int sampleRate = 16000;
	int sampleSize = 16000;

	std::string modelPath = R"(dependencies\vosk-model-en-us-0.22)";

	mVoiceInputTaker.Init(sampleRate, sampleSize);
	mRecognizer.Init(sampleRate, modelPath);

	std::cout << "Started Running" << std::endl;

	mIsRunning = true;
	mIsStartRecognizing = false;
	
	while (mIsRunning)
	{
		run();
	}
	
	std::cout << "End Running" << std::endl;
}

void MainManager::run()
{
	std::vector<ALCshort> input = mVoiceInputTaker.GetInput();

	if (!mIsStartRecognizing)
	{
		std::cout << "Getting Ready for Recognizer" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));
		std::cout << "Starting to Recognition" << std::endl;
		mIsStartRecognizing = true;

		std::cout << "Accepted Commands: start, the end, run, yes, no, elimination, go ahead" << std::endl;
	}

	int result = mRecognizer.Recognize(input, 16000);

	std::cout << std::to_string(result) << std::endl;
}
