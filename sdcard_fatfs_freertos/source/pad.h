


#ifndef PAD_H_
#define PAD_H_


#include "global.h"
#include "directories.h"

#define PAD_SIZE_16BIT 524288

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

typedef struct st_requestPAD{
	uint8_t padNum;	//pad number
	uint8_t power;	//power or volume
	uint8_t i;		//audio thread index
}reqPad_t;


extern int16_t snareRam[PAD_SIZE_16BIT];
extern int16_t kickRam[PAD_SIZE_16BIT];
extern int16_t hithatRam[PAD_SIZE_16BIT];
extern int16_t tom1Ram[PAD_SIZE_16BIT];
extern int16_t tom2Ram[PAD_SIZE_16BIT];
extern int16_t tom3Ram[PAD_SIZE_16BIT];
extern int16_t crash1Ram[PAD_SIZE_16BIT];
extern int16_t crash2Ram[PAD_SIZE_16BIT];
extern int16_t chinaRam[PAD_SIZE_16BIT];


void pad_loadDefaultPads(void);
//static void pad_thrdLoadDefaultPads(void* arg);
void pad_playNoThrd(uint8_t padNum);
int16_t* pad_getRamByNumber(uint8_t padNum);




#endif



