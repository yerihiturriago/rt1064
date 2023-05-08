



#ifndef AUDIO_ENGINE_H_
#define AUDIO_ENGINE_H_


#include "global.h"


#define AUDIO_THRD_NUM			8
#define AUDIO_THRD_QUEUE_SIZE	AUDIO_THRD_NUM
#define AUDIO_THRD_STATE_AVAIL	0
#define AUDIO_THRD_STATE_BUSY	1



typedef struct st_audioEngine{
	int16_t* saiBuffer;
	uint8_t i;
	uint8_t transferDoneSAI;
	uint8_t iQ;
	SemaphoreHandle_t semph;
	uint8_t thrdState[AUDIO_THRD_NUM];
	TaskHandle_t thrds[AUDIO_THRD_NUM];
	TaskHandle_t thrdMix;
	osa_msgq_handle_t thrdQ[AUDIO_THRD_NUM];


}audioEngine_t;



extern audioEngine_t audioEngine;


void audioEng_notifyThreads(bool isISR);
void audioEng_thrdMix(void* arg);
void audioEng_init(void);
void audioEng_initThrdQueue(void);



#endif






