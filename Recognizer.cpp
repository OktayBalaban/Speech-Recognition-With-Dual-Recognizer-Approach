#include "Recognizer.h"

Recognizer::Recognizer()
{

}

int Recognizer::Init(int sampleRate, std::string model)
{
	mModel = vosk_model_new(model.c_str());

	mRecognizer1 = vosk_recognizer_new(mModel, sampleRate);
	mRecognizer2 = vosk_recognizer_new(mModel, sampleRate);

	mResultCounterThreshold = 2;
	mCounter1 = 0;
	mCounter2 = mResultCounterThreshold / 2;

	int maxAlternatives = 200;
	vosk_recognizer_set_max_alternatives(mRecognizer1, maxAlternatives);

	mAcceptedCommands = { "start", "the end", "run", "yes", "no", "elimination", "go ahead" };

	return 0;
}

int Recognizer::Recognize(std::vector<ALCshort> &buffer, int sampleSize)
{
	vosk_recognizer_accept_waveform_s(mRecognizer1, &buffer[0], sampleSize);
	mCounter1++;
	std::cout << "mCounter1:" << std::to_string(mCounter1) << std::endl;

	vosk_recognizer_accept_waveform_s(mRecognizer2, &buffer[0], sampleSize);
	mCounter2++;
	std::cout << "mCounter2:" << std::to_string(mCounter2) << std::endl;

	if (mCounter1 == mResultCounterThreshold)
	{
		std::vector<std::string> alternatives = parseResults(vosk_recognizer_result(mRecognizer1), 5.0);
		mCounter1 = 0;
			
		int result = checkResults(alternatives);

		if (result != 0)
		{
			vosk_recognizer_reset(mRecognizer2);
		}

		return result;
	}
	if (mCounter2 == mResultCounterThreshold)
	{
		std::vector<std::string> alternatives = parseResults(vosk_recognizer_result(mRecognizer2), 0.05);
		mCounter2 = 0;

		int result = checkResults(alternatives);

		if (result != 0)
		{
			vosk_recognizer_reset(mRecognizer1);
		}

		return result;
	}


	return 0;
}

std::vector<std::string> Recognizer::parseResults(std::string results, float confidenceThreshold)
{
	nlohmann::json resultsJson = nlohmann::json::parse(results);

	//std::cout << results << std::endl;

	std::vector<std::string> alternatives;

	for (const auto& alt : resultsJson["alternatives"]) {
		double confidence = alt["confidence"].get<double>();
		if (confidence > confidenceThreshold) {
			alternatives.push_back(alt["text"].get<std::string>());
		}
	}

	/*
	std::cout << "---------------------------" << std::endl;
	for (std::string alternative : alternatives)
	{
		std::cout << "alternative: " << alternative << std::endl;
	}
	std::cout << "---------------------------" << std::endl;
	*/
	return alternatives;
}

int Recognizer::checkResults(std::vector<std::string> results)
{
	std::string foundResult = "";
	//std::cout << "Checking Results" << std::endl;
	
	for (std::string& result : results)
	{
		auto it = mAcceptedCommands.find(result);

		if (it != mAcceptedCommands.end())
		{
			foundResult = result;
			std::cout << "found result: " << foundResult << std::endl;
			break;
		}
	}

	if (foundResult == "start")
	{
		std::cout << foundResult << std::endl;
		return 1;
	}
	if (foundResult == "the end")
	{
		std::cout << foundResult << std::endl;
		return 2;
	}
	if (foundResult == "run")
	{
		std::cout << foundResult << std::endl;
		return 3;
	}
	if (foundResult == "yes")
	{
		std::cout << foundResult << std::endl;
		return 4;
	}
	if (foundResult == "no")
	{
		std::cout << foundResult << std::endl;
		return 5;
	}
	if (foundResult == "elimination")
	{
		std::cout << foundResult << std::endl;
		return 6;
	}
	if (foundResult == "go ahead")
	{
		std::cout << foundResult << std::endl;
		return 7;
	}

	return 0;
	
}
