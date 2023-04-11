


#include "global.h"

TaskHandle_t fileAccessTaskHandle1;

void test(void)
{

    int16_t ii = 0;
    for(int i = 0; i<48000;i++, ii++)
    	ramAudioBuffer[i] = ii;
    start_initilizeModules();

    if (pdPASS != xTaskCreate(test_FileAccessTask1, "test_FileAccessTask1", ACCESSFILE_TASK_STACK_SIZE, NULL, ACCESSFILE_TASK_PRIORITY, &fileAccessTaskHandle1))
    {
    	printf("fail task create: file access task 1\r\n");
        return;
    }

}



void test_FileAccessTask1(void *pvParameters)
{
    UINT bytesWritten   = 0U;
    uint32_t writeTimes = 1U;
    FRESULT error;

    xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);

    char read[20];
    int br;
    error = f_open(&g_fileObject1, _T("/test.txt"), FA_READ|FA_WRITE);
    PRINTF("f_open: %d\n\r", error);
    error = f_read(&g_fileObject1, read, sizeof(read), &br);
    PRINTF("f_read: %d, br = %d\n\r", error, br);
    PRINTF("read: %s\n\r", read);


    vTaskSuspend(NULL);
}






