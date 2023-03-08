/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    MIMXRT1064_Project_SD.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1064.h"
#include "fsl_debug_console.h"
#include "fsl_sd_disk.h"
#include "sdmmc_config.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
#define TASK_STACK_SIZE (1024U)
#define TASK_PRIORITY (configMAX_PRIORITIES - 1U)
void thrd_sd(void* a);
void thrd_main(void* a);
void SDCARD_DetectCallBack(bool isInserted, void *userData);
bool g_cardInserted = false;
bool g_cardInsertStatus = false;
/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

//    PRINTF("Hello World\n");

    /* Force the counter to be placed into memory. */
    int i = 0 ;
    printf("Hello World\n\r");
    xTaskCreate(thrd_sd, "thrd_sd", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(thrd_main, "thrd_main", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    vTaskStartScheduler();
    /* Enter an infinite loop, just incrementing a counter. */
    printf("main while\n\r");
    while(1) {
//    	GPIO_WritePinOutput(BOARD_INITPINS_LED_F14_GPIO, BOARD_INITPINS_LED_F14_GPIO_PIN, 1);
//    	printf("Hello World\n\r");
//        for(i = 0; i < 8000000; i++)__asm volatile ("nop");
//        GPIO_WritePinOutput(BOARD_INITPINS_LED_F14_GPIO, BOARD_INITPINS_LED_F14_GPIO_PIN, 0);
//        printf("Hello World\n\r");
        for(i = 0; i < 8000000; i++)__asm volatile ("nop");
    }
    return 0 ;
}

void thrd_main(void* a)
{
	for(int i = 0; i < 8000000; i++)__asm volatile ("nop");
	printf("thrd_main\n\r");
	int i = 0;
//	vTaskDelay(1000);
	while(1)
	{
		GPIO_WritePinOutput(BOARD_INITPINS_LED_F14_GPIO, BOARD_INITPINS_LED_F14_GPIO_PIN, 1);
//    	printf("Hello World\n\r");
		for(i = 0; i < 8000000; i++)__asm volatile ("nop");
//	    	vTaskDelay(300);
		GPIO_WritePinOutput(BOARD_INITPINS_LED_F14_GPIO, BOARD_INITPINS_LED_F14_GPIO_PIN, 0);
//	        vTaskDelay(300);
//        printf("Hello World\n\r");
		for(i = 0; i < 8000000; i++)__asm volatile ("nop");
	}
}

void thrd_sd(void* a)
{
	printf("thread sd\n\r");
	int r;

	BOARD_SD_Config(&g_sd, SDCARD_DetectCallBack, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY, NULL);


//	SD_Init(&g_sd);



	r = SD_HostInit(&g_sd);
	printf("sd_hostInit = %d\n\r", r);
	if(r == kStatus_Success)
	{
		while(1)
		{
			if(g_cardInserted != g_cardInsertStatus)
			{
				g_cardInserted = g_cardInsertStatus;
				if(g_cardInserted)
				{
					printf("card inserted\n\r");
					printf("power off\n\r");
	                SD_SetCardPower(&g_sd, false);
	                printf("power on\n\r");
	                SD_SetCardPower(&g_sd, true);
	                if (SD_CardInit(&g_sd))
					{
						printf("SD card init failed.\r\n");
						return;
					}

	                printf("mounting sd...\n\r");
	            	r = f_mount(&FATFS_System_0, (const TCHAR*)"2:/", 1);
	            	printf("f_mount 2: r = %d\n\r", r);
				}
			}
			if(!g_cardInserted)
			{
				printf("card is not inserted. Waiting...\r\n");
				for(int i = 0; i < 80000000; i++);
			}

		}
	}
	else
	{
		printf("sd host init failed \r\n");
	}
	return;

//
//	r = f_mount(&FATFS_System_0, (const TCHAR*)"0:", 1);
//	printf("f_mount 0: r = %d\n\r", r);
//	r = f_mount(&FATFS_System_0, (const TCHAR*)"1:", 1);
//	printf("f_mount 1: r = %d\n\r", r);
	//    printf("opening...\n\r", r);
	//    r = f_open(&FATFS_File_0, (const TCHAR*)"test.txt", FA_WRITE);
	//    printf("f_open. r = %d\n\r", r);
}

void SDCARD_DetectCallBack(bool isInserted, void *userData)
{
	printf("sd_detect_callback: %d\r\n", isInserted);
	g_cardInsertStatus = isInserted;
}
