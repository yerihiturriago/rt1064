


#include "test.h"



static TaskHandle_t fileAccessTaskHandle2;
static FIL g_fileObject2;  /* File object */

void test_fileSystem(void)
{

    if (pdPASS != xTaskCreate(test_FileAccessTask1, "FileAccessTask1", ACCESSFILE_TASK_STACK_SIZE, NULL,
                              ACCESSFILE_TASK_PRIORITY, &fileAccessTaskHandle1))
    {
        return;
    }



    if (pdPASS != xTaskCreate(test_FileAccessTask2, "FileAccessTask2", ACCESSFILE_TASK_STACK_SIZE, NULL,
                              ACCESSFILE_TASK_PRIORITY, &fileAccessTaskHandle2))
    {
        return;
    }

}


void test_FileAccessTask1(void *pvParameters)
{
    UINT bytesWritten   = 0U;
    uint32_t writeTimes = 1U;
    FRESULT error;

    xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);

    while (1)
    {
        error = f_open(&g_fileObject1, _T("/dir_1/test1.txt"), FA_WRITE);
        if (error)
        {
            if (error == FR_EXIST)
            {
                PRINTF("File exists.\r\n");
            }
            /* if file not exist, creat a new file */
            else if (error == FR_NO_FILE)
            {
                if (f_open(&g_fileObject1, _T("/dir_1/test1.txt"), (FA_WRITE | FA_CREATE_NEW)) != FR_OK)
                {
                    PRINTF("Create file failed.\r\n");
                    break;
                }
            }
            else
            {
                PRINTF("Open file failed.\r\n");
                break;
            }
        }
        /* write append */
        if (f_lseek(&g_fileObject1, g_fileObject1.obj.objsize) != FR_OK)
        {
            PRINTF("lseek file failed.\r\n");
            break;
        }

        error = f_write(&g_fileObject1, (const uint8_t*)"task1", strlen("task1"), &bytesWritten);
        if ((error) || (bytesWritten != strlen("task1")))
        {
            PRINTF("Write file failed.\r\n");
            break;
        }
        f_close(&g_fileObject1);

        if (++writeTimes > DEMO_TASK_ACCESS_SDCARD_TIMES)
        {
            PRINTF("TASK1: finished.\r\n");
            writeTimes = 1U;
            xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
            continue;
        }
        {
            PRINTF("TASK1: write file successed.\r\n");
        }
    }

    vTaskSuspend(NULL);
}



void test_FileAccessTask2(void *pvParameters)
{
    UINT bytesWritten   = 0U;
    uint32_t writeTimes = 1U;
    FRESULT error;

    xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);

    while (1)
    {
        error = f_open(&g_fileObject2, _T("/dir_1/test2.txt"), FA_WRITE);
        if (error)
        {
            if (error == FR_EXIST)
            {
                PRINTF("File exists.\r\n");
            }
            /* if file not exist, creat a new file */
            else if (error == FR_NO_FILE)
            {
                if (f_open(&g_fileObject2, _T("/dir_1/test2.txt"), (FA_WRITE | FA_CREATE_NEW)) != FR_OK)
                {
                    PRINTF("Create file failed.\r\n");
                    break;
                }
            }
            else
            {
                PRINTF("Open file failed.\r\n");
                break;
            }
        }
        /* write append */
        if (f_lseek(&g_fileObject2, g_fileObject2.obj.objsize) != FR_OK)
        {
            PRINTF("lseek file failed.\r\n");
            break;
        }

        error = f_write(&g_fileObject2, (const uint8_t*)"task2", strlen("task2"), &bytesWritten);
        if ((error) || (bytesWritten != strlen("task2")))
        {
            PRINTF("Write file failed. \r\n");
            break;
        }
        f_close(&g_fileObject2);

        if (++writeTimes > DEMO_TASK_ACCESS_SDCARD_TIMES)
        {
            PRINTF("TASK2: finished.\r\n");
            writeTimes = 1U;
            xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
            continue;
        }
        {
            PRINTF("TASK2: write file successed.\r\n");
        }
    }

    vTaskSuspend(NULL);
}





