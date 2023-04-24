


#ifndef AUDIO_H_
#define AUDIO_H_



#include "global.h"


#define AUDIO_THRD_NUM	8

typedef struct st_audioEngine{
	int16_t* mainBuffer;
	uint8_t i;
	TaskHandle_t thrds[8];
	QueueHandle_t thrdQ;

}audioEngine_t;
extern audioEngine_t audioEngine;


void audio_play(const char* fileName);
static void audio_playThrd(void* arg);
void audio_mixBuffer(int16_t* toMix, uint32_t startIndex, uint32_t length);
void audio_padPlay(uint8_t padNum, uint8_t power);
void audio_thrdPadPlay(void* arg);
TaskHandle_t audio_getNextThread(void);
void audio_initEngine(void);


#endif








