#ifndef __ADC_H_
#define __ADC_H_

#include "stm32f10x.h"
#include "rtthread.h"

extern __IO uint16_t adc_raw_data;
extern	rt_mq_t battery_mq;

void adc_Init();
void battery_check(void *param);

#endif

