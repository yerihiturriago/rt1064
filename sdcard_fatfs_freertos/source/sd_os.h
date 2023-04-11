


#ifndef SD_H
#define SD_H


#include "global.h"


extern TaskHandle_t fileAccessTaskHandle1;
extern sd_card_t g_sd;

/*! @brief Task stack size. */
#define CARDDETECT_TASK_STACK_SIZE (1024U)
/*! @brief Task stack priority. */
#define CARDDETECT_TASK_PRIORITY (configMAX_PRIORITIES - 1U)


void sd_os_cardDetectTask(void *pvParameters);
void SDCARD_DetectCallBack(bool isInserted, void *userData);
status_t sd_os_mountDrive(void);
void sd_os_init(void);




#endif











