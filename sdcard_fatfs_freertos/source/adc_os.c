



#include "adc_os.h"




void adc_os_init(void)
{
//	uint8_t r;
//	if (pdPASS != (r = xTaskCreate(adc_os_thrdReadAdc, "audio thrd pad play", 1536, NULL,
//					ACCESSFILE_TASK_PRIORITY,
//					NULL)))
//	{
//		printf("error creating adc thrd. r = %d\r\n", r);
//		return;
//	}
}

void adc_os_readADC(void* arg)
{
	EnableIRQ(ADC1_IRQn);
	ADC_SetChannelConfig(ADC1_PERIPHERAL, ADC1_CH0_CONTROL_GROUP, &ADC1_channels_config[0]);

}

void ADC1_IRQHandler(void)
{
//	logApp("adc interrupt\r\n");
	uint32_t value = ADC_GetChannelConversionValue(ADC1_PERIPHERAL, ADC1_CH0_CONTROL_GROUP);
	printf("adc interrupt. value %d\r\n", value);
	SDK_ISR_EXIT_BARRIER;
	DisableIRQ(ADC1_IRQn);
}






