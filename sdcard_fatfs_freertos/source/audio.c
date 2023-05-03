


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

void audio_initThrdQueue(void)
{

	for(int i = 0; i < AUDIO_THRD_NUM;i++)
	{
		if(KOSA_StatusSuccess != OSA_MsgQCreate(&(audioEngine.thrdQ[i]), AUDIO_THRD_QUEUE_SIZE, sizeof(reqPad_t)))
		{
			printf("error creating msg queue\r\n");
			return;
		}
	}
}


void audio_initEngine(void)
{
	int r;
	audio_initThrdQueue();
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
	uint32_t iRam = 0;
	uint8_t transferDone = 0;
	uint8_t value = 0;
	uint8_t i = *((uint8_t*)arg);
	TickType_t tick = pdMS_TO_TICKS( 200 );
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
		xSemaphoreTake(audioEngine.semph, portMAX_DELAY);
		audioEngine.thrdState[i] = AUDIO_THRD_STATE_BUSY;
		transferDone = audioEngine.transferDoneSAI;
		xSemaphoreGive(audioEngine.semph);

		while(1)
		{
			if(iRam >= PAD_SIZE_16BIT)
				break;
			if(audioEngine.thrdState[i] == AUDIO_THRD_STATE_AVAIL)
				break;
			padRam = pad_getRamByNumber(reqPad.padNum);
//			logApp("thread waiting notification\r\n");
//			xSemaphoreTake(semph_td, portMAX_DELAY);
			xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
			logApp("thrd[%d]: %d. task notification taken\r\n", i);
			audio_mixBufferControlled(padRam, &transferDone, &iRam);
		}
		iRam = 0;
		logApp("thrd[%d]: %d. pad thread finished. iRam = %d\r\n", i, iRam);
	}
	vTaskDelete(NULL);
}


void audio_mixBufferControlled(int16_t* toMix, uint8_t* transferDone, uint32_t* iRam)
{
	uint32_t sizeDataTransfer;
	if(PAD_SIZE_16BIT - *iRam >= SAI_BUFFER_HALF_SIZE)
		sizeDataTransfer = SAI_BUFFER_HALF_SIZE;
	else
		sizeDataTransfer = PAD_SIZE_16BIT - *iRam;
	logApp("mixing. iRam = %d, sizeDatatransfer = %d\r\n", *iRam, sizeDataTransfer);
//	logApp("mixing. addr = %d\r\n", toMix+(*iRam));
	audio_mixBuffer(toMix+(*iRam), *transferDone ? SAI_BUFFER_HALF_SIZE:0, sizeDataTransfer);
	*iRam += sizeDataTransfer;
}


void audio_padPlay(uint8_t padNum, uint8_t power)
{
	const reqPad_t reqPad = {
		.power  = power,
		.padNum = padNum
	};
//	logApp("req: padNum = %d, power = %d\r\n", padNum, power);
	osa_msgq_handle_t* queue = audio_getNextQueue();
	if(KOSA_StatusSuccess != OSA_MsgQPut(queue, (osa_msg_handle_t)&reqPad))
	{
		printf("audio_padPlay(): error msg queue putting\r\n");
		return;
	}

}





