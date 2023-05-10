




#ifndef SAI_OS_H_
#define SAI_OS_H_

#include "global.h"


extern bool g_saiTransferDone;
extern __DATA(RAM4) int16_t saiBuffer[SAI_BUFFER_SIZE];
extern __DATA(RAM4) int16_t filePlayBuffer[SAI_BUFFER_HALF_SIZE];
extern sai_transfer_t xfer[1];

extern const UBaseType_t xArrayIndex;
extern SemaphoreHandle_t semph_td;

void sai_os_init(void);
void fun_edma_callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData);
void fun_edma_halfTransferCallback(struct _edma_handle *handle, void *userData, bool transferDone, uint32_t tcds);



#endif



