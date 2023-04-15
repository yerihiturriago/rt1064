




#ifndef SAI_OS_H_
#define SAI_OS_H_

#include "global.h"

#define SAI_NUMBER_CHANNELS				2 //stereo
#define SAI_BYTES_PER_SAMPLES  			2
#define SAI_MONO_SAMPLES_IN_1SECOND		48000
#define SAI_BUFFER_SIZE		   			SAI_MONO_SAMPLES_IN_1SECOND*SAI_NUMBER_CHANNELS //96000 = number_channels * 48k samples
#define SAI_BUFFER_SIZE_BYTES  			SAI_BUFFER_SIZE*SAI_BYTES_PER_SAMPLES
#define SAI_BUFFER_HALF_SIZE 			SAI_BUFFER_SIZE/2
#define SAI_BUFFER_HALF_SIZE_BYTES 		SAI_BUFFER_SIZE_BYTES/2

extern bool g_saiTransferDone;
extern __DATA(RAM4) int16_t ramBuffer[SAI_BUFFER_SIZE];
extern __DATA(RAM4) int16_t filePlayBuffer[SAI_BUFFER_HALF_SIZE];
extern sai_transfer_t xfer[1];


void sai_os_init(void);
void fun_edma_callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData);
void fun_edma_halfTransferCallback(struct _edma_handle *handle, void *userData, bool transferDone, uint32_t tcds);



#endif



