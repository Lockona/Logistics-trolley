#include <stm32f10x.h>
#include "main.h"
#include "delay.h"
#include "stm32f10x_conf.h"
int16_t ce_time = -1;
void sr04_Init()
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
//	EXTI_InitStruct.EXTI_Line = EXTI_Line11;
//	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
//	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStruct);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
	GPIOB->ODR &= ~(1<<10);
//	EXTI_ClearITPendingBit(EXTI_Line11);
}
int16_t i = 0;
void get_distan()
{
	int t = 0;

	GPIOB->ODR |= 1<<10;
	delay_ms(1);
	GPIOB->ODR &= ~(1<<10);
	while((t = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11))  == 0)
		;
	ce_time = TIM4->CNT;
	while((t = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11))  != 0)
		;
	ce_time = TIM4->CNT - ce_time;
}

