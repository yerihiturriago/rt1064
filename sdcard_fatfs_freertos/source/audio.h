


#ifndef AUDIO_H_
#define AUDIO_H_



#include "global.h"



extern osa_msgq_handle_t g_queue;

void audio_play(const char* fileName);
static void audio_playThrd(void* arg);

void audio_padPlay(uint8_t padNum, uint8_t power);
void audio_thrdPadPlay(void* arg);












#endif








