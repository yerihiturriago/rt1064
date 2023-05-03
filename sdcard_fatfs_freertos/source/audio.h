


#ifndef AUDIO_H_
#define AUDIO_H_



#include "global.h"



extern osa_msgq_handle_t g_queue;

void audio_play(const char* fileName);
static void audio_playThrd(void* arg);
void audio_mixBuffer(int16_t* toMix, uint32_t startIndex, uint32_t length);
void audio_padPlay(uint8_t padNum, uint8_t power);
void audio_thrdPadPlay(void* arg);
TaskHandle_t* audio_getNextThread(void);
void audio_initEngine(void);
void audio_initThrdQueue(void);
osa_msgq_handle_t* audio_getNextQueue(void);
void audio_mixBufferControlled(int16_t* toMix, uint8_t* transferDone, uint32_t* iRam);




#endif








