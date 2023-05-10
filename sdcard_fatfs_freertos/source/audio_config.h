

#ifndef AUDIO_CONFIG_H_
#define AUDIO_CONFIG_H_




#define SAI_NUMBER_CHANNELS				2 //stereo
#define SAI_BYTES_PER_SAMPLES  			2
#define SAI_MONO_SAMPLES_IN_1ms			48
#define SAI_MONO_SAMPLES_IN_1SECOND		48000
#define SAI_STEREO_SAMPLES_IN_1ms		SAI_MONO_SAMPLES_IN_1ms*SAI_NUMBER_CHANNELS
#define SAI_STEREO_SAMPLES_IN_1SECOND	SAI_MONO_SAMPLES_IN_1SECOND*SAI_NUMBER_CHANNELS
#define SAI_BUFFER_SIZE					48*4*2 //48 samples * number channels * double buffer
#define SAI_BUFFER_SIZE_BYTES			SAI_BUFFER_SIZE*SAI_BYTES_PER_SAMPLES
#define SAI_BUFFER_HALF_SIZE 			AUDIO_BUFFER_SIZE/2
#define SAI_BUFFER_HALF_SIZE_BYTES 		AUDIO_BUFFER_SIZE_BYTES/2


#define AUDIO_BUFFER_SIZE_1ms			SAI_STEREO_SAMPLES_IN_1ms	  //9600
#define AUDIO_BUFFER_SIZE_100ms			AUDIO_BUFFER_SIZE*100	  //9600
#define AUDIO_BUFFER_SIZE_500ms			AUDIO_BUFFER_SIZE_100ms*5 //48000
#define AUDIO_BUFFER_SIZE_1s			AUDIO_BUFFER_SIZE*1000	  //96000

#define AUDIO_BUFFER_SIZE_100ms_bytes	AUDIO_BUFFER_SIZE_100ms*SAI_BYTES_PER_SAMPLES //19200 bytes
#define AUDIO_BUFFER_SIZE_500ms_bytes	AUDIO_BUFFER_SIZE_500ms*SAI_BYTES_PER_SAMPLES //96000
#define AUDIO_BUFFER_SIZE_1s_bytes		AUDIO_BUFFER_SIZE_1s*SAI_BYTES_PER_SAMPLES	  //192000

#define AUDIO_BUFFER_MIX_SIZE			AUDIO_BUFFER_SIZE_500ms		//tamaño del buffer de mezcla


#define AUDIO_BUFFER_SIZE		   		AUDIO_BUFFER_SIZE_1ms*4
#define AUDIO_BUFFER_SIZE_BYTES  		AUDIO_BUFFER_SIZE*SAI_BYTES_PER_SAMPLES

#endif


