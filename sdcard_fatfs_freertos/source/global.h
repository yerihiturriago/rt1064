


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
#include "fsl_sai_edma.h"
#include "peripherals.h"
#include "audio_config.h"
#include "sai_os.h"
#include "sd_os.h"
#include "test.h"
#include "adc_os.h"
#include "start.h"
#include "wav.h"
#include "audio_utils.h"
#include "audio_mix.h"
#include "audio_engine.h"
#include "audio.h"
#include "pad.h"
#include "file_os.h"
#include "logApp.h"
#include "button.h"


#ifndef GLOBAL_H_
#define GLOBAL_H_


#define STCD_ADDR(address) (edma_tcd_t *)(((uint32_t)(address) + 32UL) & ~0x1FU)


extern FATFS g_fileSystem; /* File system object */
extern TaskHandle_t fileAccessTaskHandle1;
extern FIL g_fileObject1;  /* File object */

#endif








