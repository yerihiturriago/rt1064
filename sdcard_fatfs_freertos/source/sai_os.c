


#include "sai_os.h"



void sai_os_init(void)
{
    EDMA_SetCallback(SAI1_SAI_Tx_eDMA_Handle.dmaHandle, fun_edma_halfTransferCallback, NULL);
    EDMA_TcdEnableInterrupts(STCD_ADDR(SAI1_SAI_Tx_eDMA_Handle.tcd), kEDMA_MajorInterruptEnable | kEDMA_HalfInterruptEnable);
    int r = SAI_TransferSendLoopEDMA(SAI1_PERIPHERAL, &SAI1_SAI_Tx_eDMA_Handle, &xfer[0], 1);
}



void fun_edma_callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
//	printf("sai callback. %d\r\n", ((edma_handle_t*)handle->dmaHandle)->channel);

}

void fun_edma_halfTransferCallback(struct _edma_handle *handle, void *userData, bool transferDone, uint32_t tcds)
{
//	printf("sai half t. callback: transferDone %d\r\n", transferDone);
}

