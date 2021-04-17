#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "portaudio.h"

#define PA_SAMPLE_TYPE  paUInt8
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512
#define NUM_SECONDS 5
#define NUM_CHANNELS 2

typedef unsigned char DataType;
typedef struct
{
    DataType* data;
    bool stopFlag;
    bool confirmFlag;
} AudioData;

int recordCallback(const void *inputBuffer, void *outputBuffer,unsigned long framesPerBuffer,const PaStreamCallbackTimeInfo* timeInfo,PaStreamCallbackFlags statusFlags,void *userData)
{
    DataType *data = ((AudioData*) userData)->data;
    const DataType *rptr = (const DataType*)inputBuffer;
    for(int i = 0; i < 100; i++)
    {
        *data++ = *rptr++;
    }
    //if(audioData->stopFlag)
    {
      //  audioData->confirmFlag = true;
      //  return paComplete;
    }
    
    return paComplete;
}


int playCallback(const void *inputBuffer, void *outputBuffer,unsigned long framesPerBuffer,const PaStreamCallbackTimeInfo* timeInfo,PaStreamCallbackFlags statusFlags,void *userData)
{
    AudioData *audioData = (AudioData*) userData;
    DataType *wptr = (DataType*)outputBuffer;
    for(int i = 0; i < 100; i++)
    {
        *wptr++ = *(audioData->data)++;
    }
    if(audioData->stopFlag)
    {
        return paComplete;
    }
    return paContinue;
}

int main()
{

    PaStreamParameters inputParameters, outputParameters;
    PaStream* inputStream;// *outputStream;
    AudioData audioData;
    audioData.stopFlag = false;
    audioData.confirmFlag = false;
    audioData.data = (DataType*)malloc(100);
    PaError error = paNoError;
   
    error = Pa_Initialize();
    inputParameters.device = Pa_GetDefaultInputDevice();
    if(inputParameters.device == paNoDevice)
    {
        printf("No input device found!\n");fflush(stdout);
    }

    inputParameters.channelCount = 2;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    error = Pa_OpenStream(&inputStream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, &audioData);
    if(error != paNoError) {printf("Eorror at open the steam!\n");fflush(stdout);}
    error = Pa_StartStream(inputStream);
    if(error != paNoError) {printf("Eorror at start the steam!\n");fflush(stdout);}
    printf("Recording now --------------------------------\n");fflush(stdout);

//---------------------------------------------------------
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    //error = Pa_OpenStream(&outputStream, NULL, &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, playCallback, data);
    if(error != paNoError) {printf("Eorror at open the steam!\n");fflush(stdout);}
    //error = Pa_StartStream(outputStream);
    if(error != paNoError) {printf("Eorror at start the steam!\n");fflush(stdout);}
    printf("Speaking starts --------------------------------\n");fflush(stdout);
//--------------------------------------------------------

    Pa_Sleep(1000);
    audioData.stopFlag = true;
    //while(!audioData.confirmFlag){}
    while(Pa_IsStreamActive(inputStream) == 1)
    {
        Pa_Sleep(1000);
    }
    error = Pa_CloseStream(inputStream );
    //error = Pa_CloseStream(outputStream);
    Pa_Terminate();
    free(audioData.data);
}
