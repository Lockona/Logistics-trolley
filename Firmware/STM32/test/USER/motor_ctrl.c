#include <stdio.h>
#include <math.h>
#include "main.h"
#include "can.h"
#include "rtthread.h"
#include "motor_ctrl.h"
#include "encoder.h"
#include "delay.h"

struct Inc_pid r_pid_val = {5, 36, 0, 0, 0, 0};
struct Inc_pid l_pid_val = {5, 36, 0, 0, 0, 0};

rt_int16_t expect_speed = 0;

void MOTOR_PWM_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef Tim_TimeBaseInitStruct;
    TIM_OCInitTypeDef Tim_OCInitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    Tim_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    Tim_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    Tim_TimeBaseInitStruct.TIM_Period = 999;
    Tim_TimeBaseInitStruct.TIM_Prescaler = 71;
    TIM_TimeBaseInit(TIM1, &Tim_TimeBaseInitStruct);
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    Tim_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    Tim_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    Tim_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    Tim_OCInitStruct.TIM_Pulse = 0;
    TIM_OC1Init(TIM1, &Tim_OCInitStruct);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    Tim_OCInitStruct.TIM_Pulse = 0;
    TIM_OC4Init(TIM1, &Tim_OCInitStruct);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    Tim_TimeBaseInitStruct.TIM_Period = 20000;
    Tim_TimeBaseInitStruct.TIM_Prescaler = 71;
    TIM_TimeBaseInit(TIM4, &Tim_TimeBaseInitStruct);
    Tim_OCInitStruct.TIM_Pulse = 1500;
    TIM_OC1Init(TIM4, &Tim_OCInitStruct);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
    TIM_CtrlPWMOutputs(TIM4, ENABLE);
}

void MOTOR_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIOA->ODR |= (3 << 4) | (1 << 12);
    GPIOB->ODR |= (3 << 14);
}

__inline void left_wheel_ctrl(int16_t pwm)
{
    if (pwm > 0)
    {
        TIM1->CCR4 = pwm;
    }
    else if(pwm <= 0)
    {
        TIM1->CCR4 = 0;
    }
}
__inline void right_wheel_ctrl(int16_t pwm)
{
    if (pwm > 0)
    {
        TIM1->CCR1 = pwm;
    }
    else if(pwm <= 0)
    {
        TIM1->CCR1 = 0;
    }
}


void stop(void)
{
	TIM1->CCR1 = 0;
	TIM1->CCR4 = 0;
}

void wheel_ctrl_task(void *param)
{
	char buff[2];
    rt_int16_t pwm_r = 0,pwm_l = 0;
    float err = 0, sum_error, right_wheel_real_speed = 0,left_wheel_real_speed = 0;
    float last_speed_l = 0, last_speed_r = 0,p;
    while (1)
    {
//        rt_mq_recv(speed_mq, &expect_speed, sizeof(rt_int16_t), 0);
        if (rt_sem_take(wheel_flag_sem, RT_WAITING_FOREVER) == RT_EOK)
        {
			buff[0] = L_Pulse;
			buff[1] = R_Pulse;
			CAN_Send_MSG('S',buff,2);
			L_Pulse = (L_Pulse>0)?(L_Pulse):(L_Pulse*-1);
			R_Pulse = (R_Pulse>0)?(R_Pulse):(R_Pulse*-1);
			
            right_wheel_real_speed = 3.14 * 6.5* R_Pulse / 780  * 100;
            r_pid_val.new_error = expect_speed - right_wheel_real_speed;
			pwm_r = (int16_t)(r_pid_val.KP*(r_pid_val.new_error - r_pid_val.last_error)+r_pid_val.KI*r_pid_val.new_error+r_pid_val.KD*(r_pid_val.new_error - 2*r_pid_val.last_error+r_pid_val.prev_error) );
			right_wheel_ctrl(pwm_r);
			
			left_wheel_real_speed = 3.14 * 6.5* L_Pulse / 780  * 100;
            l_pid_val.new_error = expect_speed - left_wheel_real_speed;
			pwm_l = (int16_t)(l_pid_val.KP*(l_pid_val.new_error - l_pid_val.last_error)+l_pid_val.KI*l_pid_val.new_error+l_pid_val.KD*(l_pid_val.new_error - 2*l_pid_val.last_error+l_pid_val.prev_error) );
			left_wheel_ctrl(pwm_l);
			
			r_pid_val.prev_error = r_pid_val.last_error;
			r_pid_val.last_error = r_pid_val.new_error;
			l_pid_val.prev_error = l_pid_val.last_error;
			l_pid_val.last_error = l_pid_val.new_error;
        }
    }
}

rt_uint16_t angle = 0;
void setAngle(void *param)
{
    while (1)
    {
        if (rt_sem_take(angle_sem, RT_WAITING_FOREVER) == RT_EOK)
        {

            TIM4->CCR1 = angle;
        }
    }
}
