


#include "logApp.h"

osa_msgq_handle_t logAppQ;

void logApp_init(void)
{
	if(OSA_MsgQCreate(&logAppQ, LOG_APP_Q_SIZE, sizeof(logReq_t)) != KOSA_StatusSuccess)
	{
		printf("error creating log app queue\r\n");
		return;
	}
	if(pdPASS != xTaskCreate(logApp_thrd, "audio thrd pad play", 1024, NULL, ACCESSFILE_TASK_PRIORITY, NULL))
	{
		printf("error creating logApp thread\r\n");
		return;
	}
}

void logApp(char* format, ...)
{
	char* buffer = pvPortMalloc(sizeof(char)*200);
	memset(buffer, 0, sizeof(char)*200);

	va_list argList;
	va_start(argList, format);
	vsprintf(buffer, format, argList);
	va_end(argList);

	logReq_t req;
	memset(req.buff, 0, sizeof(req.buff));
	sprintf(req.buff, "%s", buffer);
	OSA_MsgQPut(&logAppQ, &req);
	vPortFree(buffer);
}


void logApp_thrd(void* arg)
{
	logReq_t req;
	memset(&req, 0, sizeof(req));
	printf("logApp thrd started\r\n");

	while(1)
	{
		OSA_MsgQGet(&logAppQ, &req, osaWaitForever_c);
		printf(req.buff);
	}
}



