

#include "start.h"

static void start_mainThread(void* arg);

void start_initModules(void)
{
    sai_os_init();
    sd_os_init();
//    pad_loadDefaultPads();
}

void start_main(void)
{

    if (pdPASS !=
        xTaskCreate(start_mainThread, "main thread", 2048, NULL, (configMAX_PRIORITIES - 2U), &fileAccessTaskHandle1))
    {
    	printf("error creating card detect task\r\n");
        return;
    }
}


static void start_mainThread(void* arg)
{
	xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
//	xTaskNotifyGive(fileAccessForPad);
//	vTaskDelay(1000);
	printf("main thread working\r\n");
//	test_playBullet();
//	audio_play("bullet.wav");

	pad_loadDefaultPads();
//	while(1);
	vTaskSuspend(NULL);
}
