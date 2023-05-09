




#include "sai_os.h"

bool g_saiTransferDone = true;
int16_t saiBuffer[SAI_BUFFER_SIZE];
__DATA(RAM4) int16_t filePlayBuffer[AUDIO_BUFFER_SIZE_500ms];
sai_transfer_t xfer[1] = {
    {
        .data     = (uint8_t*)&saiBuffer[0],
        .dataSize = SAI_BUFFER_SIZE_BYTES,
    }
};

const UBaseType_t xArrayIndex = 1;
SemaphoreHandle_t semph_td = NULL;


void sai_os_init(void)
{
    memset(saiBuffer, 0, sizeof(saiBuffer));
    semph_td = xSemaphoreCreateBinary();
    audioEngine.semph = xSemaphoreCreateBinary();
    audio_mixInit();

    EDMA_SetCallback(SAI1_SAI_Tx_eDMA_Handle.dmaHandle, fun_edma_halfTransferCallback, NULL);
    EDMA_TcdEnableInterrupts(STCD_ADDR(SAI1_SAI_Tx_eDMA_Handle.tcd), kEDMA_MajorInterruptEnable | kEDMA_HalfInterruptEnable);
    int r = SAI_TransferSendLoopEDMA(SAI1_PERIPHERAL, &SAI1_SAI_Tx_eDMA_Handle, &xfer[0], 1);

}


void fun_edma_halfTransferCallback(struct _edma_handle *handle, void *userData, bool transferDone, uint32_t tcds)
{
	BaseType_t higherPriority = pdFALSE;
	xSemaphoreTakeFromISR(audioEngine.semph, &higherPriority);
	g_saiTransferDone = transferDone;
	audioEngine.transferDoneSAI = transferDone;

	xSemaphoreTakeFromISR(mixCh.semph, &higherPriority);
	if(mixCh.i >= AUDIO_BUFFER_MIX_SIZE - 1)
		mixCh.i = 0;

//	memset(transferDone ? &saiBuffer[SAI_BUFFER_HALF_SIZE]:&saiBuffer[0], 0, SAI_BUFFER_HALF_SIZE_BYTES);
	memcpy(transferDone ? &saiBuffer[SAI_BUFFER_HALF_SIZE]:&saiBuffer[0], &(mixCh.buffer[mixCh.i]), SAI_BUFFER_HALF_SIZE_BYTES);
	memset(&mixCh.buffer[mixCh.i], 0, AUDIO_BUFFER_SIZE);
//	printf("sai: mixCh.i = %d\r\n", mixCh.i);
	(mixCh.i + SAI_BUFFER_HALF_SIZE) < AUDIO_BUFFER_MIX_SIZE ? (mixCh.i += SAI_BUFFER_HALF_SIZE):(mixCh.i += AUDIO_BUFFER_MIX_SIZE - mixCh.i);
	mixCh.j = (mixCh.i+SAI_BUFFER_HALF_SIZE);

	xSemaphoreGiveFromISR(mixCh.semph, NULL);
	xSemaphoreGiveFromISR(audioEngine.semph, NULL);

//	if(audioEngine.thrdMix != NULL)
//		xTaskNotifyFromISR(audioEngine.thrdMix, 0, eNoAction, pdFALSE);

	for(int i = 0; i < AUDIO_THRD_NUM; i++)
		if(audioEngine.thrds[i] != NULL)
			xTaskNotifyFromISR(audioEngine.thrds[i], 0, eNoAction, pdFALSE);
//	printf("sai half t. callback: transferDone %d\r\n", transferDone);
}

void fun_edma_callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
//	printf("sai callback. %d\r\n", ((edma_handle_t*)handle->dmaHandle)->channel);

}





