


#ifndef PAD_H_
#define PAD_H_


#include "global.h"
#include "directories.h"




#define PAD_SNARE	0
#define PAD_KICK	1
#define PAD_HITHAT	2
#define PAD_TOM1	3
#define PAD_TOM2	4
#define PAD_TOM3	5
#define PAD_CRASH1	6
#define PAD_CRASH2	7
#define PAD_CHINA	8
#define PAD_SPLASH	9

#define PAD_MAX_POWER 124

//
//typedef struct st_audioPadChannel
//{
//	int16_t* buffer[PAD_SAMPLE_NUMBER]; //pointer a ram
//	uint32_t i;							//indice
//	float volume;
//	SemaphoreHandle_t semph;
//}AudioPadChannel_t;
//



void pad_loadDefaultPads(void);
//static void pad_thrdLoadDefaultPads(void* arg);
void pad_playNoThrd(uint8_t padNum);
int16_t* pad_getRamByNumber(uint8_t padNum);



#endif



