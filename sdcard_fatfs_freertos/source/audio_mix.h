

#ifndef AUDIO_MIX_H_
#define AUDIO_MIX_H_


#include "global.h"


typedef struct st_requestPAD{
	uint8_t padNum;	//pad number
	uint8_t power;	//power or volume
	uint8_t i;		//audio thread index
}reqPad_t;


typedef struct st_audioMixConfig
{
	int16_t* toMix;			//buffer de datos a mezclar
	int16_t* saiBuffer;		//buffer del modulo sai
	float volume;			//volumen
	uint8_t power;  		//intensidad del hit
	uint8_t padNum;

} AudioMixConfig_t;


void audio_mixInSaiBuffer(int16_t* toMix, uint32_t startIndex, uint32_t length);
void audio_mixBufferControlled(int16_t* toMix, uint8_t* transferDone, uint32_t* iRam);
void audio_mixInChannel(AudioMixConfig_t* config);
void audio_getConfigByRequest(reqPad_t* reqPad, AudioMixConfig_t* config);


#endif


