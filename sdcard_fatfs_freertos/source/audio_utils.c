


#include "audio_utils.h"







TaskHandle_t* audio_getNextThread(void)
{
	printf("audio get audio thread\r\n");
	audioEngine.i >= (AUDIO_THRD_NUM-1) ? audioEngine.i = 0:audioEngine.i++;
//	printf("task state = %d\r\n", eTaskGetState(audioEngine.thrds[audioEngine.i]));
	if(audioEngine.thrdState[audioEngine.i] == AUDIO_THRD_STATE_BUSY)
		audioEngine.thrdState[audioEngine.i] = AUDIO_THRD_STATE_AVAIL;
	return &audioEngine.thrds[audioEngine.i];
}




osa_msgq_handle_t* audio_getNextQueue(void)
{
	uint8_t i = audioEngine.iQ;
	i >= (AUDIO_THRD_NUM-1) ? i = 0:(i += 1);
	audioEngine.iQ = i;
	return &(audioEngine.thrdQ[i]);
}


void audio_initRamBuffers(void)
{
	memset(snareRam, 0, sizeof(snareRam));

}


float audio_calculateVolumeByPower(uint8_t power)
{
	return ((float)power/PAD_MAX_POWER);
}




