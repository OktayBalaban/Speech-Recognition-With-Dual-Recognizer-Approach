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
    //std::cout << "In Get Input" << std::endl;
    alcCaptureStart(mDevice);

    std::vector<ALCshort> buffer(mSampleSize);
    ALCint samplesIn;

    // Wait for some samples to become available
    do {
        alcGetIntegerv(mDevice, ALC_CAPTURE_SAMPLES, 1, &samplesIn);
    } while (samplesIn < mSampleSize);

    // Grab the samples
    alcCaptureSamples(mDevice, &buffer[0], mSampleSize);

    // We've got the samples, stop capturing
    alcCaptureStop(mDevice);
    

    // Do something with the samples
    // In a real program, you'd probably write them to a file or send them over the network...

    return buffer;
}

void VoiceInputTaker::closeDevice()
{
    alcCaptureCloseDevice(mDevice);
}
