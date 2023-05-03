




#include "sai_os.h"

bool g_saiTransferDone = true;
__DATA(RAM4) int16_t ramBuffer[SAI_BUFFER_SIZE];
__DATA(RAM4) int16_t filePlayBuffer[SAI_BUFFER_HALF_SIZE];
sai_transfer_t xfer[1] = {
    {
        .data     = (uint8_t*)&ramBuffer[0],
        .dataSize = SAI_BUFFER_SIZE_BYTES,
    }
};

const UBaseType_t xArrayIndex = 1;
SemaphoreHandle_t semph_td = NULL;


void sai_os_init(void)
{
    memset(ramBuffer, 0, sizeof(ramBuffer));
    semph_td = xSemaphoreCreateBinary();

    EDMA_SetCallback(SAI1_SAI_Tx_eDMA_Handle.dmaHandle, fun_edma_halfTransferCallback, NULL);
    EDMA_TcdEnableInterrupts(STCD_ADDR(SAI1_SAI_Tx_eDMA_Handle.tcd), kEDMA_MajorInterruptEnable | kEDMA_HalfInterruptEnable);
    int r = SAI_TransferSendLoopEDMA(SAI1_PERIPHERAL, &SAI1_SAI_Tx_eDMA_Handle, &xfer[0], 1);

}


void fun_edma_halfTransferCallback(struct _edma_handle *handle, void *userData, bool transferDone, uint32_t tcds)
{
	BaseType_t higherPriority = pdFALSE;
	memset(transferDone ? &ramBuffer[SAI_BUFFER_HALF_SIZE]:&ramBuffer[0], 0, SAI_BUFFER_HALF_SIZE_BYTES);
	g_saiTransferDone = transferDone;
	xSemaphoreGiveFromISR(semph_td, NULL);
//	if(audioEngine.thrds[0] != NULL)

//	 vTaskNotifyGiveIndexedFromISR(audioEngine.thrds[1],
//	                                   xArrayIndex,
//	                                   &higherPriority);

//	printf("sai half t. callback: transferDone %d\r\n", transferDone);
}

void fun_edma_callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
//	printf("sai callback. %d\r\n", ((edma_handle_t*)handle->dmaHandle)->channel);

}





