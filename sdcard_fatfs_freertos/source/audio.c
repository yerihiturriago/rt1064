


#include "audio.h"

uint8_t g_isPlayingAudio = false;

audioEngine_t audioEngine = {
	.mainBuffer = ramBuffer,
	.i 			= 0,
	.iQ 		= 0,
};

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
//	if(eTaskGetState(audioEngine.thrds[audioEngine.i]) < eSuspended)
//		vTaskSuspend(audioEngine.thrds[audioEngine.i]);
	return &audioEngine.thrds[audioEngine.i];
}

osa_msgq_handle_t audio_getNextQueue(void)
{
	uint8_t i = audioEngine.iQ;
	i >= (AUDIO_THRD_NUM-1) ? i = 0:(i += 1);
	audioEngine.iQ = i;
	return audioEngine.thrdQ[i];
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
	uint8_t i = *((uint8_t*)arg);
	if(i >= AUDIO_THRD_NUM)
		return;
	vPortFree(arg);
	reqPad_t reqPad = {0};
	while(1)
	{
		OSA_MsgQGet(&g_queue, &reqPad, osaWaitForever_c);
//		OSA_MsgQGet(&(audioEngine.thrdQ[i]), &reqPad, osaWaitForever_c);
		logApp("thrd[%d]: pad = %d, power = %d\r\n", i, reqPad.padNum, reqPad.power);

	}
	vTaskDelete(NULL);
}

void audio_padPlay(uint8_t padNum, uint8_t power)
{
//	reqPad_t* reqPad = (reqPad_t*)pvPortMalloc(sizeof(reqPad_t));
//	reqPad->padNum = padNum;
//	reqPad->power  = power;
	const reqPad_t reqPad = {
		.power  = power,
		.padNum = padNum
	};
	osa_msgq_handle_t handle = audio_getNextQueue();
//	if(KOSA_StatusSuccess != OSA_MsgQPut(&handle, (osa_msg_handle_t)&reqPad))
	if(KOSA_StatusSuccess != OSA_MsgQPut(&g_queue, (osa_msg_handle_t)&reqPad))
	{
		printf("audio_padPlay(): error msg queue putting\r\n");
		return;
	}

}







