/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>
#include "fsl_sd.h"
#include "fsl_debug_console.h"
#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "limits.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "sdmmc_config.h"
#include <cr_section_macros.h>
#include "fsl_common.h"
#include "fsl_semc.h"
#include "fsl_flexio_i2s_edma.h"
#include "peripherals.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_TASK_GET_SEM_BLOCK_TICKS 1U
#define DEMO_TASK_ACCESS_SDCARD_TIMES 2U
/*! @brief Task stack size. */
#define ACCESSFILE_TASK_STACK_SIZE (1024U)
/*! @brief Task stack priority. */
#define ACCESSFILE_TASK_PRIORITY (configMAX_PRIORITIES - 2U)

/*! @brief Task stack size. */
#define CARDDETECT_TASK_STACK_SIZE (1024U)
/*! @brief Task stack priority. */
#define CARDDETECT_TASK_PRIORITY (configMAX_PRIORITIES - 1U)

#define EXAMPLE_SEMC_CLK_FREQ      CLOCK_GetFreq(kCLOCK_SemcClk)
#define SEMC_EXAMPLE_DATALEN    (0x1000U)
#define SEMC_EXAMPLE_WRITETIMES (1000U)
#define EXAMPLE_SEMC_START_ADDRESS (0x80000000U)

uint32_t sdram_writeBuffer[SEMC_EXAMPLE_DATALEN];
uint32_t sdram_readBuffer[SEMC_EXAMPLE_DATALEN];

status_t BOARD_InitSEMC(void);
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_PowerOffSDCARD(void);
void BOARD_PowerOnSDCARD(void);
/*!
 * @brief SD card access task 1.
 *
 * @param pvParameters Task parameter.
 */
static void FileAccessTask1(void *pvParameters);

/*!
 * @brief SD card access task 2.
 *
 * @param pvParameters Task parameter.
 */
static void FileAccessTask2(void *pvParameters);

/*!
 * @brief SD card detect task.
 *
 * @param pvParameters Task parameter.
 */
static void CardDetectTask(void *pvParameters);

/*!
 * @brief call back function for SD card detect.
 *
 * @param isInserted  true,  indicate the card is insert.
 *                    false, indicate the card is remove.
 * @param userData
 */
static void SDCARD_DetectCallBack(bool isInserted, void *userData);

/*!
 * @brief make filesystem.
 */
static status_t DEMO_MakeFileSystem(void);


/*******************************************************************************
 * Variables
 ******************************************************************************/
static FATFS g_fileSystem; /* File system object */
static FIL g_fileObject1;  /* File object */
static FIL g_fileObject2;  /* File object */

static const uint8_t s_buffer1[] = {'T', 'A', 'S', 'K', '5', '\r', '\n'};
static const uint8_t s_buffer2[] = {'T', 'A', 'S', 'K', '6', '\r', '\n'};
/*! @brief SD card detect flag  */
static volatile bool s_cardInserted     = false;
static volatile bool s_cardInsertStatus = false;
/*! @brief Card semaphore  */
static SemaphoreHandle_t s_CardDetectSemaphore = NULL;
/*! @brief file access task handler */
TaskHandle_t fileAccessTaskHandle1;
TaskHandle_t fileAccessTaskHandle2;
void SEMC_SDRAMReadWrite32Bit(void);

//__DATA(RAM4) unsigned char myBuffer[1024];
__DATA(RAM4) int sdram_data[100];
#define BUFFER_HALF_SIZE 32*100
#define STCD_ADDR(address) (edma_tcd_t *)(((uint32_t)(address) + 32UL) & ~0x1FU)
int16_t s_buffer[BUFFER_HALF_SIZE*2];

void * p_sai_data;

sai_transfer_t xfer[1] = {
    {
        .data     = (uint8_t*)&s_buffer[0],
        .dataSize = BUFFER_HALF_SIZE*2,
    }
};

void fun_edma_callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
//	printf("sai callback. %d\r\n", ((edma_handle_t*)handle->dmaHandle)->channel);

}

void fun_edma_halfTransferCallback(struct _edma_handle *handle, void *userData, bool transferDone, uint32_t tcds)
{
//	printf("sai half t. callback: transferDone %d\r\n", transferDone);
}

/*******************************************************************************
 * Code
 ******************************************************************************/
static void SDCARD_DetectCallBack(bool isInserted, void *userData)
{
    s_cardInsertStatus = isInserted;
    xSemaphoreGiveFromISR(s_CardDetectSemaphore, NULL);
}

static void CardDetectTask(void *pvParameters)
{
    s_CardDetectSemaphore = xSemaphoreCreateBinary();

    BOARD_SD_Config(&g_sd, SDCARD_DetectCallBack, BOARD_SDMMC_SD_HOST_IRQ_PRIORITY, NULL);

    /* SD host init function */
    if (SD_HostInit(&g_sd) == kStatus_Success)
    {
        while (true)
        {
            /* take card detect semaphore */
            if (xSemaphoreTake(s_CardDetectSemaphore, portMAX_DELAY) == pdTRUE)
            {
                if (s_cardInserted != s_cardInsertStatus)
                {
                    s_cardInserted = s_cardInsertStatus;

                    if (s_cardInserted)
                    {
                        PRINTF("\r\nCard inserted.\r\n");
                        /* power off card */
                        SD_SetCardPower(&g_sd, false);
                        /* power on the card */
                        SD_SetCardPower(&g_sd, true);
                        /* make file system */
                        if (DEMO_MakeFileSystem() != kStatus_Success)
                        {
                            continue;
                        }
                        xTaskNotifyGive(fileAccessTaskHandle1);
//                        xTaskNotifyGive(fileAccessTaskHandle2);
                    }
                }

                if (!s_cardInserted)
                {
                    PRINTF("\r\nPlease insert a card into board.\r\n");
                }
            }
        }
    }
    else
    {
        PRINTF("\r\nSD host init fail\r\n");
    }

    vTaskSuspend(NULL);
}

/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitSEMC();
    BOARD_InitBootPeripherals();


    PRINTF("\r\nSDCARD fatfs freertos, sdram, flexio i2s example.\r\n");

//    SEMC_SDRAMReadWrite32Bit();
    sdram_data[0] = 55;
    sdram_data[255999] = 55;
    printf("ram data[0] = %d, [256000] = %d\r\n", sdram_data[0], sdram_data[255999]);

    p_sai_data = (void*)sdram_data;

    uint16_t ii = 0;
    for(int i = 0; i<BUFFER_HALF_SIZE;i++, ii++)
    	s_buffer[i] = ii;
    EDMA_SetCallback(SAI1_SAI_Tx_eDMA_Handle.dmaHandle, fun_edma_halfTransferCallback, NULL);
    EDMA_TcdEnableInterrupts(STCD_ADDR(SAI1_SAI_Tx_eDMA_Handle.tcd), kEDMA_MajorInterruptEnable | kEDMA_HalfInterruptEnable);
    int r = SAI_TransferSendLoopEDMA(SAI1_PERIPHERAL, &SAI1_SAI_Tx_eDMA_Handle, &xfer[0], 1);
    while(1);

    return 0;




    if (pdPASS != xTaskCreate(FileAccessTask1, "FileAccessTask1", ACCESSFILE_TASK_STACK_SIZE, NULL,
                              ACCESSFILE_TASK_PRIORITY, &fileAccessTaskHandle1))
    {
        return -1;
    }

//    if (pdPASS != xTaskCreate(FileAccessTask2, "FileAccessTask1", ACCESSFILE_TASK_STACK_SIZE, NULL,
//                              ACCESSFILE_TASK_PRIORITY, &fileAccessTaskHandle2))
//    {
//        return -1;
//    }

    if (pdPASS !=
        xTaskCreate(CardDetectTask, "CardDetectTask", CARDDETECT_TASK_STACK_SIZE, NULL, CARDDETECT_TASK_PRIORITY, NULL))
    {
        return -1;
    }

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* Scheduler should never reach this point. */
    while (true)
    {
    }
}

static status_t DEMO_MakeFileSystem(void)
{
    FRESULT error;
    const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};
    BYTE work[FF_MAX_SS];

    if (f_mount(&g_fileSystem, driverNumberBuffer, 0U))
    {
        PRINTF("Mount volume failed.\r\n");
        return kStatus_Fail;
    }

#if (FF_FS_RPATH >= 2U)
    error = f_chdrive((char const *)&driverNumberBuffer[0U]);
    if (error)
    {
        PRINTF("Change drive failed.\r\n");
        return kStatus_Fail;
    }
#endif
    return kStatus_Success;
}

static void FileAccessTask1(void *pvParameters)
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
//    while (1)
//    {
//        error = f_open(&g_fileObject1, _T("/dir_1/test1.txt"), FA_WRITE);
//        if (error)
//        {
//            if (error == FR_EXIST)
//            {
//                PRINTF("File exists.\r\n");
//            }
//            /* if file not exist, creat a new file */
//            else if (error == FR_NO_FILE)
//            {
//                if (f_open(&g_fileObject1, _T("/dir_1/test1.txt"), (FA_WRITE | FA_CREATE_NEW)) != FR_OK)
//                {
//                    PRINTF("Create file failed.\r\n");
//                    break;
//                }
//            }
//            else
//            {
//                PRINTF("Open file failed.\r\n");
//                break;
//            }
//        }
//        /* write append */
//        if (f_lseek(&g_fileObject1, g_fileObject1.obj.objsize) != FR_OK)
//        {
//            PRINTF("lseek file failed.\r\n");
//            break;
//        }
//
//        error = f_write(&g_fileObject1, s_buffer1, sizeof(s_buffer1), &bytesWritten);
//        if ((error) || (bytesWritten != sizeof(s_buffer1)))
//        {
//            PRINTF("Write file failed.\r\n");
//            break;
//        }
//        f_close(&g_fileObject1);
//
//        if (++writeTimes > DEMO_TASK_ACCESS_SDCARD_TIMES)
//        {
//            PRINTF("TASK1: finished.\r\n");
//            writeTimes = 1U;
//            xTaskNotifyWait(ULONG_MAX, ULONG_MAX, NULL, portMAX_DELAY);
//            continue;
//        }
//        {
//            PRINTF("TASK1: write file successed.\r\n");
//        }
//    }

    vTaskSuspend(NULL);
}

static void FileAccessTask2(void *pvParameters)
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

        error = f_write(&g_fileObject2, s_buffer2, sizeof(s_buffer2), &bytesWritten);
        if ((error) || (bytesWritten != sizeof(s_buffer2)))
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


status_t BOARD_InitSEMC(void)
{
    semc_config_t config;
    semc_sdram_config_t sdramconfig;
    uint32_t clockFrq = EXAMPLE_SEMC_CLK_FREQ;

    /* Initializes the MAC configure structure to zero. */
    memset(&config, 0, sizeof(semc_config_t));
    memset(&sdramconfig, 0, sizeof(semc_sdram_config_t));

    /* Initialize SEMC. */
    SEMC_GetDefaultConfig(&config);
    config.dqsMode = kSEMC_Loopbackdqspad; /* For more accurate timing. */
    SEMC_Init(SEMC, &config);

    /* Configure SDRAM. */
    sdramconfig.csxPinMux           = kSEMC_MUXCSX0;
    sdramconfig.address             = 0x80000000;
    sdramconfig.memsize_kbytes      = 32 * 1024; /* 32MB = 32*1024*1KBytes*/
    sdramconfig.portSize            = kSEMC_PortSize16Bit;
    sdramconfig.burstLen            = kSEMC_Sdram_BurstLen8;
    sdramconfig.columnAddrBitNum    = kSEMC_SdramColunm_9bit;
    sdramconfig.casLatency          = kSEMC_LatencyThree;
    sdramconfig.tPrecharge2Act_Ns   = 18; /* Trp 18ns */
    sdramconfig.tAct2ReadWrite_Ns   = 18; /* Trcd 18ns */
    sdramconfig.tRefreshRecovery_Ns = 67; /* Use the maximum of the (Trfc , Txsr). */
    sdramconfig.tWriteRecovery_Ns   = 12; /* 12ns */
    sdramconfig.tCkeOff_Ns =
        42; /* The minimum cycle of SDRAM CLK off state. CKE is off in self refresh at a minimum period tRAS.*/
    sdramconfig.tAct2Prechage_Ns       = 42; /* Tras 42ns */
    sdramconfig.tSelfRefRecovery_Ns    = 67;
    sdramconfig.tRefresh2Refresh_Ns    = 60;
    sdramconfig.tAct2Act_Ns            = 60;
    sdramconfig.tPrescalePeriod_Ns     = 160 * (1000000000 / clockFrq);
    sdramconfig.refreshPeriod_nsPerRow = 64 * 1000000 / 8192; /* 64ms/8192 */
    sdramconfig.refreshUrgThreshold    = sdramconfig.refreshPeriod_nsPerRow;
    sdramconfig.refreshBurstLen        = 1;
    return SEMC_ConfigureSDRAM(SEMC, kSEMC_SDRAM_CS0, &sdramconfig, clockFrq);
}


void SEMC_SDRAMReadWrite32Bit(void)
{
    uint32_t index;
    uint32_t datalen = SEMC_EXAMPLE_DATALEN;
    uint32_t *sdram  = (uint32_t *)EXAMPLE_SEMC_START_ADDRESS; /* SDRAM start address. */
    bool result      = true;

    PRINTF("\r\n SEMC SDRAM Memory 32 bit Write Start, Start Address 0x%x, Data Length %d !\r\n", sdram, datalen);
    /* Prepare data and write to SDRAM. */
    for (index = 0; index < datalen; index++)
    {
        sdram_writeBuffer[index] = index;
        sdram[index]             = sdram_writeBuffer[index];
    }

    PRINTF("\r\n SEMC SDRAM Read 32 bit Data Start, Start Address 0x%x, Data Length %d !\r\n", sdram, datalen);
    /* Read data from the SDRAM. */
    for (index = 0; index < datalen; index++)
    {
        sdram_readBuffer[index] = sdram[index];
    }

    PRINTF("\r\n SEMC SDRAM 32 bit Data Write and Read Compare Start!\r\n");
    /* Compare the two buffers. */
    while (datalen--)
    {
        if (sdram_writeBuffer[datalen] != sdram_readBuffer[datalen])
        {
            result = false;
            break;
        }
    }

    if (!result)
    {
        PRINTF("\r\n SEMC SDRAM 32 bit Data Write and Read Compare Failed!\r\n");
    }
    else
    {
        PRINTF("\r\n SEMC SDRAM 32 bit Data Write and Read Compare Succeed!\r\n");
    }
}

