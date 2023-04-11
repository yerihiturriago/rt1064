


#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>
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
#include "fsl_os_abstraction.h"

#include "testing/testing.h"
#include "sd_os.h"
#include "sai_os.h"
#include "start.h"


#ifndef GLOBAL_H
#define GLOBAL_H


#define ACCESSFILE_TASK_STACK_SIZE (1024U)
#define ACCESSFILE_TASK_PRIORITY   (configMAX_PRIORITIES - 2U)
#define STCD_ADDR(address) (edma_tcd_t *)(((uint32_t)(address) + 32UL) & ~0x1FU)


extern __DATA(RAM4) int16_t ramAudioBuffer[48000];
extern FATFS g_fileSystem; /* File system object */
extern FIL g_fileObject1;  /* File object */
extern volatile bool s_cardInserted;
extern volatile bool s_cardInsertStatus;
extern sd_card_t g_sd;
extern sai_transfer_t xfer[1];


#endif

