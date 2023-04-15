


#ifndef AUDIO_H_
#define AUDIO_H_



#include "global.h"


void audio_play(const char* fileName);
static void audio_playThrd(void* arg);
void audio_mixBuffer(int16_t* toMix, uint32_t startIndex, uint32_t length);




#endif








