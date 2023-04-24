


#ifndef LOG_APP_H_
#define LOG_APP_H_


#include "global.h"

#define LOG_APP_Q_SIZE 8

typedef struct st_logReq{
	char buff[60];
	uint8_t i;
}logReq_t;

extern osa_msgq_handle_t logAppQ;

void logApp(char* format, ...);
void logApp_init(void);
void logApp_thrd(void* arg);


#endif


