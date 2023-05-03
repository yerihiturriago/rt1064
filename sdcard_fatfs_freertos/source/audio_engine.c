



#include "audio_engine.h"



audioEngine_t audioEngine = {
	.mainBuffer 	 = ramBuffer,
	.i 				 = 0,
	.iQ 			 = 0,
	.transferDoneSAI = 0,
	.semph			 = NULL,
	.thrdState  	 = {0,0,0,0,0,0,0,0},
	.thrds			 = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
//	.thrdQ			 = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};


void audioEng_notifyThreads(void)
{
	for(int i = 0; i < AUDIO_THRD_NUM; i++)
		if(audioEngine.thrdState[i] == AUDIO_THRD_STATE_BUSY)
			xTaskNotifyGive(audioEngine.thrds[i]);
}





