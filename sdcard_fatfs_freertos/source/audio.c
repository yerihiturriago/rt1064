


#include "audio.h"

uint8_t g_isPlayingAudio = false;

osa_msgq_handle_t g_queue;


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
			audio_mixInSaiBuffer(filePlayBuffer, g_saiTransferDone ? SAI_BUFFER_HALF_SIZE:0, SAI_BUFFER_HALF_SIZE);

		}
	}
	vTaskDelete(NULL);
}





void audio_thrdPadPlay(void* arg)
{
	uint8_t transferDone = 0;
	uint8_t value = 0;
	uint8_t i = *((uint8_t*)arg);
	TickType_t tick = pdMS_TO_TICKS( 200 );
	AudioMixConfig_t config;

	if(i >= AUDIO_THRD_NUM)
		return;
	vPortFree(arg);
	logApp("threadId = %d. Working...\r\n", i);
	reqPad_t reqPad = {0};
	int16_t* padRam = NULL;
	while(1)
	{
		OSA_MsgQGet(&(audioEngine.thrdQ[i]), &reqPad, osaWaitForever_c);
		logApp("thrd[%d]: pad = %d, power = %d\r\n", i, reqPad.padNum, reqPad.power);
		audio_getConfigByRequest(&reqPad, &config);

		xSemaphoreTake(audioEngine.semph, portMAX_DELAY);
		audioEngine.thrdState[i] = AUDIO_THRD_STATE_BUSY;
		transferDone = audioEngine.transferDoneSAI;
		xSemaphoreGive(audioEngine.semph);

		while(1)
		{
			if(config.iMix >= PAD_SIZE_16BIT-1)
				break;
			xSemaphoreTake(audioEngine.semph, portMAX_DELAY);
			transferDone = audioEngine.transferDoneSAI;
			if(audioEngine.thrdState[i] == AUDIO_THRD_STATE_AVAIL)
			{
				xSemaphoreGive(audioEngine.semph);
				break;
			}
			xSemaphoreGive(audioEngine.semph);
			xSemaphoreTake(mixCh.semph, portMAX_DELAY);
//			logApp("thrd[%d]: iRam = %d, mixCh.i = %d\r\n", i, config.iMix, mixCh.i);
			audio_mixInChannel(&config);
			xSemaphoreGive(mixCh.semph);
			xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
//			logApp("thrd[%d]. task notification taken\r\n", i);
		}
		config.iMix = 0;
		xSemaphoreTake(audioEngine.semph, portMAX_DELAY);
		audioEngine.thrdState[i] = AUDIO_THRD_STATE_AVAIL;
		xSemaphoreGive(audioEngine.semph);
//		logApp("thrd[%d]: %d. pad thread finished. iRam = %d\r\n", i, iRam);
	}
	vTaskDelete(NULL);
}



void audio_padPlay(uint8_t padNum, uint8_t power)
{
	const reqPad_t reqPad = {
		.power  = power,
		.padNum = padNum
	};
//	logApp("req: padNum = %d, power = %d\r\n", padNum, power);
	osa_msgq_handle_t* queue = audio_getNextQueue();
	if(audioEngine.thrdState[audioEngine.iQ] != AUDIO_THRD_STATE_AVAIL)
		audioEngine.thrdState[audioEngine.iQ] = AUDIO_THRD_STATE_AVAIL;
	if(KOSA_StatusSuccess != OSA_MsgQPut(queue, (osa_msg_handle_t)&reqPad))
	{
		printf("audio_padPlay(): error msg queue putting\r\n");
		return;
	}

}





