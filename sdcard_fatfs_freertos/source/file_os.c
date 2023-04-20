

#include "file_os.h"



file_os_t fileOs = {
		.buffer   = NULL,
		.name	  = NULL,
		.openMode = FA_READ,
		.fileObj  = &g_fileObject1,
};

uint8_t file_open(file_os_t* file)
{
	uint8_t r;
	if((r = f_open(file->fileObj, file->name, file->openMode)))
	{
		printf("error opening file. error: %d. line %d, file %s\r\n", r, __LINE__, __FILE__);
		return r;
	}
}

uint8_t file_read(file_os_t* file, unsigned int btr, unsigned int* br)
{
	uint8_t r;
	if((r = file_open(file)))
		return r;
	if(file->buffer == NULL)
	{
		printf("file_read(): remember assign a buffer in file_os_t argument\r\n");
		return -55;
	}

	if((r = f_read(file->fileObj, file->buffer, btr, br)))
		printf("file_read(): error reading file. error: %d\r\n", r);
	return r;
}


