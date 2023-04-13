

#ifndef WAV_H_
#define WAV_H_

#include <stdint.h>


typedef struct st_wav_header
{
	uint32_t riff;
	uint32_t fileSize;
	uint32_t waveStr;
	uint32_t fmtHeader;
	uint32_t chunkSectionSize;
	uint16_t wavType;
	uint16_t monoOrStereo;
	uint32_t sampleFrecuency;
	uint32_t bytesPerSeconds;
	uint16_t blockAlign;
	uint16_t bitsPerSample;
	uint32_t dataDescHeader;
	uint32_t sizeDataChunck;

}wav_header_t;


void wav_printHeader(wav_header_t* header);



#endif

