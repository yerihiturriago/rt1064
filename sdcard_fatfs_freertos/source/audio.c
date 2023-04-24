


#include "audio.h"

uint8_t g_isPlayingAudio = false;

audioEngine_t audioEngine = {
	.mainBuffer = ramBuffer,
	.i 			= 0,
};


void audio_play(const char* fileName)
{
	printf("audio play func\r\n");
    if (pdPASS != xTaskCreate(audio_playThrd, "audio thread", 1024, (void*)fileName, ACCESSFILE_TASK_PRIORITY, NULL))
    {
        return;
    }
}

static void audio_playThrd(void* arg)
{
	uint8_t r;
	uint32_t lseek = 0;
	wav_header_t wav;
	uint32_t fileSize;
	uint32_t numReadBytes = 0;
	uint32_t bytesToRead;
	uint8_t halfTransferCopy;

	printf("audio play thrd\r\n");


	if((r = f_open(&g_fileObject1, _T("bullet.wav"), FA_READ)) != FR_OK)
	{
		printf("error opening file: %d\r\n", r);
		return;
	}

	f_read(&g_fileObject1, &wav, 44, &lseek);
	fileSize = wav.fileSize;
	halfTransferCopy = g_saiTransferDone;
	g_isPlayingAudio = true;
	while(g_isPlayingAudio && (lseek < fileSize))
	{
		if(halfTransferCopy != g_saiTransferDone)
		{
			halfTransferCopy = g_saiTransferDone;
			if(fileSize - lseek >= SAI_BUFFER_HALF_SIZE_BYTES)
				bytesToRead = SAI_BUFFER_HALF_SIZE_BYTES;
			else
				bytesToRead = fileSize - lseek;

			f_read(&g_fileObject1, filePlayBuffer, SAI_BUFFER_HALF_SIZE_BYTES, &numReadBytes);
			lseek += bytesToRead;
			printf("lseek = %d\r\n", lseek);
			audio_mixBuffer(filePlayBuffer, g_saiTransferDone ? SAI_BUFFER_HALF_SIZE:0, SAI_BUFFER_HALF_SIZE);

		}
	}
	vTaskDelete(NULL);
}


void audio_mixBuffer(int16_t* toMix, uint32_t startIndex, uint32_t length)
{
	int j = startIndex;
	for(int i = 0; i < length; i++, j++)
		ramBuffer[j] += toMix[i];
}


TaskHandle_t audio_getNextThread(void)
{
	printf("audio get audio thread\r\n");
	audioEngine.i >= 7 ? audioEngine.i = 0:audioEngine.i++;
//	printf("task state = %d\r\n", eTaskGetState(audioEngine.thrds[audioEngine.i]));
//	if(eTaskGetState(audioEngine.thrds[audioEngine.i]) < eSuspended)
//		vTaskSuspend(audioEngine.thrds[audioEngine.i]);
	return audioEngine.thrds[audioEngine.i];
}

void audio_initEngine(void)
{

//	xTaskCreate(audio_thrdPadPlay, "audio thrd pad play", 1024,
//			(void*)i,
//			ACCESSFILE_TASK_PRIORITY,
//			&(audioEngine.thrds[0]));
//	return;
	int r;
	for(int i = 0; i < AUDIO_THRD_NUM;i++)
	{

		uint8_t* ii = (uint8_t*)pvPortMalloc(sizeof(uint8_t));
		*ii = i;
		if (pdPASS != (r = xTaskCreate(audio_thrdPadPlay, "audio thrd pad play", 1024,
				(void*)ii,
				ACCESSFILE_TASK_PRIORITY,
				&(audioEngine.thrds[i])))
			)
		{
			printf("error creating audio thrds. r = %d, index = %d\r\n", r, i);
			return;
		}
	}
}

void audio_thrdPadPlay(void* arg)
{
	uint8_t i = *((uint8_t*)arg);
	if(i >= AUDIO_THRD_NUM)
		vPortFree(arg);
	reqPad_t reqPad = {0};
//	vPortFree(arg);
//	printf("padNum = %d, power = %d\r\n", reqPad.padNum, reqPad.power);
//	printf("thread.i = %d\r\n", audioEngine.i);
//	printf("thread.i = %d\r\n", i);
//	osa_msgq_handle_t q;
//	osa_msg_handle_t  m;
//	OSA_MsgQGet(q, m, osaWaitForever_c);
	while(1)
	{
//		OSA_MsgQGet(audioEngine.thrdQ[i], &reqPad, osaWaitForever_c);
	}
	vTaskDelete(NULL);
}

void audio_padPlay(uint8_t padNum, uint8_t power)
{
	reqPad_t* reqPad = (reqPad_t*)pvPortMalloc(sizeof(reqPad_t));
	reqPad->padNum = padNum;
	reqPad->power  = power;
//	TaskHandle_t handle = audio_getAudioThread();
	printf("audio pad play\r\n");
}







