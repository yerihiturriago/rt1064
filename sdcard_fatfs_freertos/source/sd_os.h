

#ifndef SD_OS_H_
#define SD_OS_H_


#include "global.h"


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


extern TaskHandle_t fileAccessTaskHandle1;
extern TaskHandle_t fileAccessForPad;
extern sd_card_t g_sd;

extern volatile bool s_cardInserted;
extern volatile bool s_cardInsertStatus;

/*! @brief Task stack size. */
#define CARDDETECT_TASK_STACK_SIZE (1024U)
/*! @brief Task stack priority. */
#define CARDDETECT_TASK_PRIORITY (configMAX_PRIORITIES - 1U)


//void sd_os_cardDetectTask(void *pvParameters);
//void SDCARD_DetectCallBack(bool isInserted, void *userData);
//status_t sd_os_mountDrive(void);

void sd_os_init(void);
status_t sd_os_mountDrive(void);
void CardDetectTask(void *pvParameters);
void sd_os_cardDetectTask(bool isInserted, void *userData);


#endif






