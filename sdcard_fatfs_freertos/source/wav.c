

#include "global.h"


void wav_printHeader(wav_header_t* header)
{
	printf("bitsPerSample   = %d\r\n", header->bitsPerSample);
	printf("bytesPerSeconds = %d\r\n", header->bytesPerSeconds);
	printf("sampleFrecuency = %d\r\n", header->sampleFrecuency);
	printf("size            = %d\r\n", header->fileSize);
	printf("monoOrStereo    = %s\r\n", header->monoOrStereo == 1 ?"mono":"stereo");
//	printf("\r\n", header->);
}



