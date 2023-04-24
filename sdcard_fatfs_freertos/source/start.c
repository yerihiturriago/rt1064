

#include "start.h"

static void start_mainThread(void* arg);

void start_initModules(void)
{
    sai_os_init();
    sd_os_init();
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
	logApp_init();
	OSA_TimeDelay(200);
	audio_initEngine();
	int r = OSA_MsgQCreate(&g_queue, 1, sizeof(reqPad_t));
	printf("r = %s\r\n", r == KOSA_StatusSuccess ? "success":"error");
	reqPad_t reqPad = {
			.power  = 124,
			.padNum = 1,
	};
	OSA_MsgQPut(&g_queue, &reqPad);
	reqPad_t reqPadCpy = {0};

	logApp("req: padNum = %d, power = %d\r\n", reqPadCpy.padNum, reqPadCpy.power);
//	audio_padPlay(10, 124);
	while(1);
	vTaskDelete(NULL);
}
