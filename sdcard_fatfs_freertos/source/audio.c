


#include "audio.h"

uint8_t g_isPlayingAudio = false;


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
	vTaskSuspend(NULL);
}


void audio_mixBuffer(int16_t* toMix, uint32_t startIndex, uint32_t length)
{
	int j = startIndex;
	for(int i = 0; i < length; i++, j++)
		ramBuffer[j] += toMix[i];
}







