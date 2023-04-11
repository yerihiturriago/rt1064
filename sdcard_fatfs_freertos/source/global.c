


#include "global.h"



__DATA(RAM4) int16_t ramAudioBuffer[48000];
sai_transfer_t xfer[1] = {
    {
        .data     = (uint8_t*)&ramAudioBuffer[0],//(uint8_t*)&s_buffer[0],
        .dataSize = 48000,
    }
};
FATFS g_fileSystem; /* File system object */
FIL g_fileObject1;  /* File object */


volatile bool s_cardInserted     = false;
volatile bool s_cardInsertStatus = false;





