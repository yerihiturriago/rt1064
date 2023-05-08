


#include "audio_mix.h"




void audio_mixInSaiBuffer(int16_t* toMix, uint32_t startIndex, uint32_t length)
{
	int j = startIndex;
	for(int i = 0; i < length; i++, j++)
		saiBuffer[j] += toMix[i];
}



void audio_mixBufferControlled(int16_t* toMix, uint8_t* transferDone, uint32_t* iRam)
{
	uint32_t sizeDataTransfer;
	if(PAD_SIZE_16BIT - *iRam >= SAI_BUFFER_HALF_SIZE)
		sizeDataTransfer = SAI_BUFFER_HALF_SIZE;
	else
		sizeDataTransfer = PAD_SIZE_16BIT - *iRam;
	logApp("mixing. iRam = %d, sizeDatatransfer = %d\r\n", *iRam, sizeDataTransfer);
//	logApp("mixing. addr = %d\r\n", toMix+(*iRam));
	audio_mixInSaiBuffer(toMix+(*iRam), *transferDone ? SAI_BUFFER_HALF_SIZE:0, sizeDataTransfer);
	*iRam += sizeDataTransfer;
}

void audio_getConfigByRequest(reqPad_t* reqPad, AudioMixConfig_t* config)
{
	memset(config, 0, sizeof(AudioMixConfig_t));
	config->padNum = reqPad->padNum;
	config->power  = reqPad->power;
	config->toMix  = pad_getRamByNumber(reqPad->padNum);
}

void audio_mixInChannel(AudioMixConfig_t* config)
{

}










