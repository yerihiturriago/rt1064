


#include "audio.h"

uint8_t g_isPlayingAudio = false;

osa_msgq_handle_t g_queue;


void audio_play(const char* fileName)
{
	printf("audio play func\r\n");
    if (pdPASS != xTaskCreate(audio_playThrd, "audio thread", 1024, (void*)fileName, ACCESSFILE_TASK_PRIORITY, &audioEngine.thrdFilePlay))
    {
        return;
    }
}

void audio_playNoThrd(const char* fileName)
{
	uint8_t r;
	uint32_t lseek = 0;
	wav_header_t wav;
	uint32_t fileSize;
	uint32_t numReadBytes = 0;
	uint32_t bytesToRead;
	uint32_t len;
	uint8_t transferDoneCopy;

	logApp("audio play no thrd\r\n");

	if((r = f_open(&g_fileObject1, _T(fileName), FA_READ)) != FR_OK)
	{
		printf("error opening file: %d\r\n", r);
		return;
	}
	logApp("audio play no thrd: f_read wav\r\n");
	f_read(&g_fileObject1, &wav, 44, &lseek);
	fileSize = wav.fileSize;
	logApp("audio play no thrd: read file portion\r\n");
	f_read(&g_fileObject1, filePlayBuffer, SAI_BUFFER_HALF_SIZE_BYTES, &numReadBytes);
	lseek += numReadBytes;
	transferDoneCopy = g_saiTransferDone;
	g_isPlayingAudio = true;
	while((lseek < fileSize) && g_isPlayingAudio)
	{
//		logApp("audio play no thrd: semaphore take\r\n");
		xSemaphoreTake(audioEngine.semph, portMAX_DELAY);
		if(g_saiTransferDone != transferDoneCopy)
		{
			transferDoneCopy = g_saiTransferDone;
			if(fileSize - lseek >= SAI_BUFFER_HALF_SIZE_BYTES)
				bytesToRead = SAI_BUFFER_HALF_SIZE_BYTES;
			else
				bytesToRead = fileSize - lseek;
			f_read(&g_fileObject1, filePlayBuffer, bytesToRead, &numReadBytes);
//			logApp("audio_playNoThrd: lseek = %d\r\n", lseek);
			xSemaphoreTake(mixCh.semph, portMAX_DELAY);
			memcpy(&mixCh.buffer[mixCh.i], filePlayBuffer, SAI_BUFFER_HALF_SIZE_BYTES);
			xSemaphoreGive(mixCh.semph);
			lseek += numReadBytes;
		}
		xSemaphoreGive(audioEngine.semph);
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

	printf("audio play thrd\r\n");


	if((r = f_open(&g_fileObject1, _T((const char*)arg), FA_READ)) != FR_OK)
	{
		printf("error opening file: %d\r\n", r);
		return;
	}

	f_read(&g_fileObject1, &wav, 44, &lseek);
	fileSize = wav.fileSize;
	g_isPlayingAudio = true;
	while(g_isPlayingAudio && (lseek < fileSize))
	{
		xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
		xSemaphoreTake(audioEngine.semph, portMAX_DELAY);
		if(fileSize - lseek >= SAI_BUFFER_HALF_SIZE_BYTES)
			bytesToRead = SAI_BUFFER_HALF_SIZE_BYTES;
		else
			bytesToRead = fileSize - lseek;

		f_read(&g_fileObject1, filePlayBuffer, bytesToRead, &numReadBytes);
		lseek += numReadBytes;
//		logApp("lseek = %d\r\n", lseek);
		xSemaphoreTake(mixCh.semph, portMAX_DELAY);
//		audio_mixInMixCh(filePlayBuffer, SAI_BUFFER_HALF_SIZE);
		for(uint32_t i = 0; i < SAI_BUFFER_HALF_SIZE; i++)
		{
			mixCh.buffer[mixCh.i+i] += (int16_t)filePlayBuffer[i]*audioEngine.filePlay.volume;
		}
		xSemaphoreGive(mixCh.semph);
		xSemaphoreGive(audioEngine.semph);
	}
	logApp("audio thrad file: lseek = %d\r\n", lseek);
	vTaskDelete(NULL);
}





void audio_thrdPadPlay(void* arg)
{
	uint8_t value = 0;
	uint8_t id = *((uint8_t*)arg);
	TickType_t tick = pdMS_TO_TICKS( 200 );
	AudioMixConfig_t config;

	if(id >= AUDIO_THRD_NUM)
		return;
	vPortFree(arg);
	logApp("threadId = %d. Working...\r\n", id);
	reqPad_t reqPad = {0};
	int16_t* padRam = NULL;
	while(1)
	{
		OSA_MsgQGet(&(audioEngine.thrdQ[id]), &reqPad, osaWaitForever_c);
		logApp("thrd[%d]: pad = %d, power = %d\r\n", id, reqPad.padNum, reqPad.power);
		audio_getConfigByRequest(&reqPad, &config);

		xSemaphoreTake(audioEngine.semph, portMAX_DELAY);
		audioEngine.thrdState[id] = AUDIO_THRD_STATE_BUSY;
		xSemaphoreGive(audioEngine.semph);

		while(1)
		{
			if(config.iMix >= PAD_SIZE_16BIT-1)
				break;
			xSemaphoreTake(audioEngine.semph, portMAX_DELAY);
//			transferDone = audioEngine.transferDoneSAI;
			if(audioEngine.thrdState[id] == AUDIO_THRD_STATE_AVAIL)
			{
				xSemaphoreGive(audioEngine.semph);
				break;
			}
			xSemaphoreGive(audioEngine.semph);
			xSemaphoreTake(mixCh.semph, portMAX_DELAY);
//			logApp("thrd[%d]: iRam = %d, mixCh.i = %d\r\n", i, config.iMix, mixCh.id);
			audio_mixInChannel(&config);
			xSemaphoreGive(mixCh.semph);
			xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
//			logApp("thrd[%d]. task notification taken\r\n", id);
		}
		config.iMix = 0;
		xSemaphoreTake(audioEngine.semph, portMAX_DELAY);
		audioEngine.thrdState[id] = AUDIO_THRD_STATE_AVAIL;
		xSemaphoreGive(audioEngine.semph);
//		logApp("thrd[%d]: %d. pad thread finished. iRam = %d\r\n", id, iRam);
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





