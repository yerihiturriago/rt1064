



#include "audio_engine.h"



audioEngine_t audioEngine = {
	.saiBuffer 	 	 = saiBuffer,
	.filePlay 		 = {.buffer = filePlayBuffer, .i = 0, .semph = NULL, .volume = 1.0},
	.i 				 = 0,
	.iQ 			 = 0,
	.transferDoneSAI = 0,
	.semph			 = NULL,
	.thrdMix		 = NULL,
	.thrdFilePlay	 = NULL,
	.thrdState  	 = {0,0,0,0,0,0,0,0},
	.thrds			 = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
	.thrdQ			 = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};




void audioEng_init(void)
{
	int r;
	audioEng_initThrdQueue();
//	r = xTaskCreate(audioEng_thrdMix, "audio thrd mix", 1024, NULL, ACCESSFILE_TASK_PRIORITY, &audioEngine.thrdMix);
//	if(pdPASS != r)
//		printf("error creating mix thrds. r = %d\r\n", r);
	for(int i = 0; i < AUDIO_THRD_NUM;i++)
	{
		uint8_t* ii = (uint8_t*)pvPortMalloc(sizeof(uint8_t));
		*ii = i;
		if (pdPASS != (r = xTaskCreate(audio_thrdPadPlay, "audio thrd pad play", 1536,
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


void audioEng_initThrdQueue(void)
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

void audioEng_notifyThreads(bool isISR)
{
	if(isISR)
		xTaskNotifyFromISR(audioEngine.thrdMix, 0, eNoAction, pdFALSE);
	else
		xTaskNotifyGive(audioEngine.thrdMix);
	for(int i = 0; i < AUDIO_THRD_NUM; i++)
		if(audioEngine.thrdState[i] == AUDIO_THRD_STATE_BUSY)
			if(isISR)
				xTaskNotifyFromISR(audioEngine.thrds[i], 0, eNoAction, pdFALSE);
			else
				xTaskNotifyGive(audioEngine.thrds[i]);
}



void audioEng_thrdMix(void* arg)
{
	logApp("thread mix start\r\n");
	int16_t* mainBuffer = audioEngine.saiBuffer;
	uint8_t transferDone;
	while(1)
	{
		xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
		xSemaphoreTake(audioEngine.semph, portMAX_DELAY);
		transferDone = audioEngine.transferDoneSAI;
//		memcpy(transferDone ? SAI_BUFFER_HALF_SIZE:0, );
		xSemaphoreGive(audioEngine.semph);
//		logApp("mix thrd: get notification\r\n");
	}
}






