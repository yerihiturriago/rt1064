


#include <cr_section_macros.h>
#include "pad.h"

__NOINIT(RAM4) int16_t snareRam[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t kickRam[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t hithatRam[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t tom1Ram[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t tom2Ram[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t tom3Ram[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t crash1Ram[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t crash2Ram[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t chinaRam[PAD_SIZE_16BIT];



void pad_loadDefaultPads(void)
{

    if (pdPASS !=
        xTaskCreate(pad_thrdLoadDefaultPads, "load default pads", 1024, NULL, ACCESSFILE_TASK_PRIORITY, NULL))
    {
    	printf("error creating load default pads task\r\n");
        return;
    }
}


static void pad_thrdLoadDefaultPads(void* arg)
{
//	xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
	printf("pad thrd load default pads\r\n");
	uint8_t r;
	wav_header_t wav;
	uint32_t br;
	char aux[50];

	memset(aux, 0, sizeof(aux));
	sprintf(aux, "%s%s", PAD_DIR_SNARE, PAD_SNARE_STR);

	fileOs.name = (char*)pvPortMalloc(strlen(aux)+1);
	fileOs.buffer	= &wav;
	sprintf(fileOs.name, aux, "124");

	printf("fileName = %s\r\n", fileOs.name);

	if((r = file_read(&fileOs, 44, &br)))
	{
		printf("error reading header .wav: error %d\r\n", r);
		return;
	}
	fileOs.buffer = snareRam;
	wav_printHeader(&wav);

//	if((r = file_read(&fileOs, wav.fileSize, &br)))
//	{
//
//	}


	vPortFree(fileOs.name);
	vTaskSuspend(NULL);
}





