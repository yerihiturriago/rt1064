


#ifndef FILE_OS_H_
#define FILE_OS_H_


#include "global.h"


typedef struct st_file_os{
	char* name;
	FIL* fileObj;		//g_fileObject1
	uint8_t openMode; 	// FA_READ
	void* buffer;		//to reading


}file_os_t;
extern file_os_t fileOs;



uint8_t file_read(file_os_t* file, unsigned int btr, unsigned int* br);
uint8_t file_open(file_os_t* file);


#endif









