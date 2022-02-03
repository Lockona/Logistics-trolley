#include "stm32f10x.h"
#include "adc.h"
#include "rtthread.h"
#include "can.h"
#include "motor_ctrl.h"

rt_mq_t battery_mq = RT_NULL;
__IO uint16_t adc_raw_data = 0;

void adc_Init(void)
{
	GPIO_InitTypeDef gpio_handle;
	ADC_InitTypeDef adc_handle;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
	gpio_handle.GPIO_Pin  = GPIO_Pin_2;
	gpio_handle.GPIO_Mode = GPIO_Mode_AIN;
	
	GPIO_Init(GPIOA,&gpio_handle);
	
	adc_handle.ADC_Mode = ADC_Mode_Independent;
	adc_handle.ADC_ScanConvMode = DISABLE;
	adc_handle.ADC_ContinuousConvMode = ENABLE;
	adc_handle.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc_handle.ADC_DataAlign = ADC_DataAlign_Right;
	adc_handle.ADC_NbrOfChannel = 1;

	ADC_Init(ADC1,&adc_handle);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,1,ADC_SampleTime_55Cycles5);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

void battery_check(void *param)
{
	static uint8_t last_value= 100,value = 0;
	uint8_t i = 1,start_flag = 1;
	float voltage;
	rt_thread_delay(2000);
	while(1)
	{
		if(!expect_speed)
		{
			adc_raw_data += ADC_GetConversionValue(ADC1);
			if(i > 9)
			{
				voltage = (float)adc_raw_data / 10 / 4096 * 3.3;
				value = (voltage - 2.775)/(3.15 - 2.775) * 100;
				if(start_flag)
				{
					last_value = value;
					start_flag = 0;
				}
				else if((value<=last_value))
				{
					last_value = value;
					CAN_Send_MSG('B',(char*)&last_value,1);
				}
				adc_raw_data = 0;                                          
				i = 1;
			}
			else
			{
				i++;
			}
		}
		rt_thread_delay(50);
	}
	
}
