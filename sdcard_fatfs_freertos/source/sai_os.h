




#ifndef SAI_OS_H_
#define SAI_OS_H_

#include "global.h"



extern __DATA(RAM4) int16_t ramBuffer[48000];
extern sai_transfer_t xfer[1];


void sai_os_init(void);
void fun_edma_callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData);
void fun_edma_halfTransferCallback(struct _edma_handle *handle, void *userData, bool transferDone, uint32_t tcds);



#endif



