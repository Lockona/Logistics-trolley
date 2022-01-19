#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f10x.h"
#include <rthw.h>
#include <rtthread.h>
#include "main.h"
#include "delay.h"
#include "motor_ctrl.h"
#include "usart1.h"
#include "encoder.h"
#include "oled_SPI.h"
#include "can.h"
#include "adc.h"

void rt_hw_board_init(void);
void SysTick_Handler(void);

#endif
