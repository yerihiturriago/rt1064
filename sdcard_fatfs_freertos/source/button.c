


#include "button.h"


void button_init(void)
{
	printf("button init creating thread\r\n");
    if (pdPASS != xTaskCreate(button_thrdDetectKey, "audio thread", 1024, NULL, ACCESSFILE_TASK_PRIORITY, NULL))
    {
        return;
    }
}

static void button_thrdDetectKey(void* arg)
{
	uint8_t readPin = 0;
	printf("button start thrd detect key\r\n");

	while(1)
	{
		readPin = GPIO_ReadPinInput(BOARD_BUTTON_B28_GPIO, BOARD_BUTTON_B28_GPIO_PIN);
		if(readPin)
		{
			audio_padPlay(PAD_SNARE, 124);
		}
		OSA_TimeDelay(200);
	}
	vTaskDelete(NULL);
}











