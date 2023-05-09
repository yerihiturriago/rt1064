


#include "audio_mix.h"


__NOINIT(RAM4) AudioMixChannel_t mixCh;

void audio_mixInit(void)
{
	mixCh.i 	 = 0;
	mixCh.j 	 = 0;
	mixCh.volume = 0;
	mixCh.semph  = xSemaphoreCreateBinary();
}

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
	config->mixCh  = &mixCh;
	config->toMix  = pad_getRamByNumber(reqPad->padNum);
}

void audio_mixInChannel(AudioMixConfig_t* config)
{
	uint32_t i;
	int16_t* dst = config->mixCh->buffer;
	int16_t* src = config->toMix;
	uint32_t* iRam = &config->iMix;

	if(PAD_SIZE_16BIT - *iRam >= AUDIO_BUFFER_SIZE)
		config->lengthToMix = AUDIO_BUFFER_SIZE;
	else
		config->lengthToMix = PAD_SIZE_16BIT - *iRam;

	float volumeByPower = audio_calculateVolumeByPower(config->power);
	for (i = config->mixCh->i; i < config->lengthToMix; i++)
		dst[i] += src[config->iMix];
//		dst[i] += src[i]*(config->volume)*volumeByPower;
	config->iMix += config->lengthToMix - 1;
}










