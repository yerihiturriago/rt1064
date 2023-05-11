

#ifndef AUDIO_MIX_H_
#define AUDIO_MIX_H_


#include "global.h"


#define PAD_SAMPLE_NUMBER 	3
#define PAD_SIZE_16BIT 		524288


typedef struct st_requestPAD{
	uint8_t padNum;	//pad number
	uint8_t power;	//power or volume
	uint8_t i;		//audio thread index
}reqPad_t;


typedef struct st_audioMixChannel
{
	SemaphoreHandle_t semph;								//semaforo para sincronización de hilos
	uint32_t 		i;									//indice inicial de mezcla
	uint32_t    	j;									//indice final de mezcla
	int16_t 		buffer[AUDIO_BUFFER_MIX_SIZE];	//buffer de datos
	float 			volume;

} AudioMixChannel_t;



typedef struct st_audioPadChannel
{
	int16_t* buffer[PAD_SAMPLE_NUMBER]; //pointer a ram
	uint32_t i;							//indice
	float volume;
	SemaphoreHandle_t semph;
}AudioPadChannel_t;




typedef struct st_audioMixConfig
{
	AudioMixChannel_t* mixCh; 	//Mix channel
	AudioPadChannel_t* padCh;	//Pad channel
	int16_t* toMix; 	//Datos a mezclar
	uint32_t iMix;				//equivalent to iRam. Index of ram pointer
	uint32_t lengthToMix;   	//tamaño o longitud de muestras a mezclar. Data size to transfer.
//	int16_t* saiBuffer;			//buffer del modulo sai
	uint8_t power;  			//intensidad del hit
	uint8_t padNum;				//pad number

} AudioMixConfig_t;


extern AudioMixChannel_t mixCh;



extern int16_t snareRam[PAD_SIZE_16BIT];
extern int16_t kickRam[PAD_SIZE_16BIT];
extern int16_t hithatRam[PAD_SIZE_16BIT];
extern int16_t tom1Ram[PAD_SIZE_16BIT];
extern int16_t tom2Ram[PAD_SIZE_16BIT];
extern int16_t tom3Ram[PAD_SIZE_16BIT];
extern int16_t crash1Ram[PAD_SIZE_16BIT];
extern int16_t crash2Ram[PAD_SIZE_16BIT];
extern int16_t chinaRam[PAD_SIZE_16BIT];


extern AudioPadChannel_t snareCh;
extern AudioPadChannel_t kickCh;
extern AudioPadChannel_t hithatCh;
extern AudioPadChannel_t tom1Ch;
extern AudioPadChannel_t tom2Ch;
extern AudioPadChannel_t tom3Ch;
extern AudioPadChannel_t crash1Ch;
extern AudioPadChannel_t crash2Ch;
extern AudioPadChannel_t chinaCh;




void audio_mixInit(void);
void audio_mixInSaiBuffer(int16_t* toMix, uint32_t startIndex, uint32_t length);
void audio_mixBufferControlled(int16_t* toMix, uint8_t* transferDone, uint32_t* iRam);
void audio_mixInChannel(AudioMixConfig_t* config);
void audio_getConfigByRequest(reqPad_t* reqPad, AudioMixConfig_t* config);
void audio_mixInMixCh(int16_t* toMix, uint32_t length);
AudioPadChannel_t* audio_getPadChannelByNumber(uint8_t padNum);

#endif


