#include <iostream>
#include "MainManager.h"

int main()
{
    
    MainManager mainManager;
    mainManager.Init();
    
    /*
    VoskModel* model = vosk_model_new(R"(C:\Users\oktay\source\repos\SpeechRecognition\x64\Debug\model\vosk-model-en-us-0.22)");
    VoskRecognizer* recognizer = vosk_recognizer_new(model, 16000.0);
    vosk_recognizer_free(recognizer);
    vosk_model_free(model);
    */
    return 0;
}


