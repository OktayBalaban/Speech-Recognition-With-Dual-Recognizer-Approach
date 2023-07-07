#include "VoiceInputTaker.h"

VoiceInputTaker::VoiceInputTaker()
{
}

int VoiceInputTaker::Init(int sampleRate, int sampleSize)
{
    mSampleRate = sampleRate,
    mSampleSize = sampleSize,

    mDevice = alcCaptureOpenDevice(NULL, mSampleRate, AL_FORMAT_MONO16, mSampleSize);
    if (!mDevice) {
        std::cerr << "Unable to open device for capture.\n";
        return -1;
    }

    return 0;
}

std::vector<ALCshort> VoiceInputTaker::GetInput()
{

    alcCaptureStart(mDevice);

    std::vector<ALCshort> buffer(mSampleSize);
    ALCint samplesIn;

    do {
        alcGetIntegerv(mDevice, ALC_CAPTURE_SAMPLES, 1, &samplesIn);
    } while (samplesIn < mSampleSize);


    alcCaptureSamples(mDevice, &buffer[0], mSampleSize);
    alcCaptureStop(mDevice);
    

    return buffer;
}

void VoiceInputTaker::closeDevice()
{
    alcCaptureCloseDevice(mDevice);
}
