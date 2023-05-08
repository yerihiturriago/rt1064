


#ifndef AUDIO_UTILS_H_
#define AUDIO_UTILS_H_


#include "global.h"


TaskHandle_t* audio_getNextThread(void);
osa_msgq_handle_t* audio_getNextQueue(void);
void audio_initRamBuffers(void);
float audio_calculateVolumeByPower(uint8_t intensity);

#endif








