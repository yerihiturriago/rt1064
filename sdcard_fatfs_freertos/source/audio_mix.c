


#include "audio_mix.h"


__NOINIT(RAM4) AudioMixChannel_t mixCh;


__NOINIT(RAM4) int16_t snareRam[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t kickRam[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t hithatRam[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t tom1Ram[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t tom2Ram[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t tom3Ram[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t crash1Ram[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t crash2Ram[PAD_SIZE_16BIT];
__NOINIT(RAM4) int16_t chinaRam[PAD_SIZE_16BIT];


AudioPadChannel_t snareCh 	= {.buffer = {snareRam,  NULL, NULL}, .volume = 1, .i = 0, .semph = NULL};
AudioPadChannel_t kickCh 	= {.buffer = {kickRam,   NULL, NULL}, .volume = 1, .i = 0, .semph = NULL};
AudioPadChannel_t hithatCh 	= {.buffer = {hithatRam, NULL, NULL}, .volume = 1, .i = 0, .semph = NULL};
AudioPadChannel_t tom1Ch 	= {.buffer = {tom1Ram,   NULL, NULL}, .volume = 1, .i = 0, .semph = NULL};
AudioPadChannel_t tom2Ch 	= {.buffer = {tom2Ram,   NULL, NULL}, .volume = 1, .i = 0, .semph = NULL};
AudioPadChannel_t tom3Ch 	= {.buffer = {tom3Ram,   NULL, NULL}, .volume = 1, .i = 0, .semph = NULL};
AudioPadChannel_t crash1Ch 	= {.buffer = {crash1Ram, NULL, NULL}, .volume = 1, .i = 0, .semph = NULL};
AudioPadChannel_t crash2Ch 	= {.buffer = {crash2Ram, NULL, NULL}, .volume = 1, .i = 0, .semph = NULL};
AudioPadChannel_t chinaCh 	= {.buffer = {chinaRam,  NULL, NULL}, .volume = 1, .i = 0, .semph = NULL};



void audio_mixInit(void)
{
	mixCh.i 	 = 0;
	mixCh.j 	 = 0;
	mixCh.volume = 0;
	mixCh.semph  = xSemaphoreCreateBinary();

    snareCh.semph 		= xSemaphoreCreateBinary();
    kickCh.semph 		= xSemaphoreCreateBinary();
    hithatCh.semph 		= xSemaphoreCreateBinary();
    tom1Ch.semph 		= xSemaphoreCreateBinary();
    tom2Ch.semph 		= xSemaphoreCreateBinary();
    tom3Ch.semph	 	= xSemaphoreCreateBinary();
    crash1Ch.semph 		= xSemaphoreCreateBinary();
    crash2Ch.semph 		= xSemaphoreCreateBinary();
    chinaCh.semph		= xSemaphoreCreateBinary();

    audioEngine.semph 	= xSemaphoreCreateBinary();
}

void audio_mixInMixCh(int16_t* toMix, uint32_t length)
{
	for(uint32_t i = 0; i < length; i++)
	{
		mixCh.buffer[mixCh.i+i] += filePlayBuffer[i];
	}
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
	config->padCh  = audio_getPadChannelByNumber(reqPad->padNum);
	config->toMix  = pad_getRamByNumber(reqPad->padNum);
}

void audio_mixInChannel(AudioMixConfig_t* config)
{
	float volumeByPower = audio_calculateVolumeByPower(config->power);
//	logApp("volumeBypower = %.2f, volume = %.2f\r\n", volumeByPower, config->padCh->volume);
	for(int i = 0; i < SAI_BUFFER_HALF_SIZE; config->iMix++, i++)
	{
		mixCh.buffer[mixCh.i+i] += (int16_t)(config->toMix[config->iMix]*config->padCh->volume*volumeByPower);
	}
}



AudioPadChannel_t* audio_getPadChannelByNumber(uint8_t padNum)
{
	switch(padNum)
	{
		case PAD_SNARE: 	return &snareCh;
		case PAD_KICK: 		return &kickCh;
		case PAD_HITHAT: 	return &hithatCh;
		case PAD_TOM1: 		return &tom1Ch;
		case PAD_TOM2: 		return &tom2Ch;
		case PAD_TOM3: 		return &tom3Ch;
		case PAD_CRASH1: 	return &crash1Ch;
		case PAD_CRASH2: 	return &crash2Ch;
		case PAD_CHINA: 	return &chinaCh;
//		case PAD_SPLASH: 	return splas;
		default: 			return &snareCh;
	}
}








