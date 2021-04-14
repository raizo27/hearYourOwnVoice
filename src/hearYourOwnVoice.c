#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"

#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512
#define NUM_SECONDS 5
#define NUM_CHANNELS 2

typedef float SAMPLE;

int recordCallback(const void *inputBuffer, void *outputBuffer,unsigned long framesPerBuffer,const PaStreamCallbackTimeInfo* timeInfo,PaStreamCallbackFlags statusFlags,void *userData)
{
    SAMPLE *data = (SAMPLE*) userData;
    const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
    for(int i = 0; i < 100; i++)
    {
        *data++ = *rptr++;
    }
    return paComplete;
}


int playCallback(const void *inputBuffer, void *outputBuffer,unsigned long framesPerBuffer,const PaStreamCallbackTimeInfo* timeInfo,PaStreamCallbackFlags statusFlags,void *userData)
{
    SAMPLE *data = (SAMPLE*) userData;
    SAMPLE *wptr = (SAMPLE*)inputBuffer;
    for(int i = 0; i < 100; i++)
    {
        *wptr++ = *data++;
    }
    return paComplete;
}

int main()
{

    PaStreamParameters inputParameters, outputParameters;
    PaStream* inputStream, *outputStream;
    SAMPLE* data = (SAMPLE*)malloc(100);
    PaError error = paNoError;
   
    error = Pa_Initialize();
    inputParameters.device = Pa_GetDefaultInputDevice();
    if(inputParameters.device == paNoDevice)
    {
        printf("No input device found!\n");
    }

    inputParameters.channelCount = 2;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    error = Pa_OpenStream(&inputStream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, data);

}
