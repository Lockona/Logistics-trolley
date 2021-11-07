#include <stdio.h>
#include <stdlib.h>
#include "can.h"
#include "main.h"
#include "motor_ctrl.h"
#include "stm32f10x_conf.h"
CanRxMsg recv_data;
void Can_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    CAN_InitTypeDef CAN_InitStruct;
    CAN_FilterInitTypeDef CAN_FilterInitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
    NVIC_InitStruct.NVIC_IRQChannel = CAN1_RX1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    CAN_DeInit(CAN1);
    CAN_StructInit(&CAN_InitStruct);
    CAN_InitStruct.CAN_ABOM = DISABLE;
    CAN_InitStruct.CAN_AWUM = DISABLE;
    CAN_InitStruct.CAN_TTCM = DISABLE;
    CAN_InitStruct.CAN_TXFP = DISABLE;
    CAN_InitStruct.CAN_NART = DISABLE;
    CAN_InitStruct.CAN_RFLM = DISABLE;
    CAN_InitStruct.CAN_SJW = CAN_SJW_3tq;
    CAN_InitStruct.CAN_BS1 = CAN_BS1_10tq;
    CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStruct.CAN_Prescaler = 4;
    CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;
    CAN_Init(CAN1, &CAN_InitStruct);
    CAN_FilterInitStruct.CAN_FilterNumber = 1;
    CAN_FilterInitStruct.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStruct.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStruct.CAN_FilterIdHigh = 0x00;
    CAN_FilterInitStruct.CAN_FilterIdLow = CAN_ID_STD | CAN_RTR_DATA;
    CAN_FilterInitStruct.CAN_FilterMaskIdHigh = 0x0;
    CAN_FilterInitStruct.CAN_FilterMaskIdLow = 0x0;

    CAN_FilterInitStruct.CAN_FilterFIFOAssignment = CAN_FIFO1;
    CAN_FilterInitStruct.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStruct);
    CAN_ClearFlag(CAN1, CAN_FLAG_FMP1);
    CAN_ITConfig(CAN1, CAN_IT_FMP1, ENABLE);
}
void can_recv_to_ctrl(void *param)
{
    rt_int16_t val = 0;
    while (1)
    {
        if (rt_sem_take(can_recv_sem, RT_WAITING_FOREVER) == RT_EOK)
        {
            switch (recv_data.StdId)
            {
            case 'M':
				r_pid_val.old_error = 0;
				r_pid_val.new_error = 0;
				r_pid_val.sum_error = 0;
				l_pid_val.old_error = 0;
				l_pid_val.new_error = 0;
				l_pid_val.sum_error = 0;
                expect_speed = atoi((char *)recv_data.Data);
			
                //rt_mq_send(speed_mq, &val, sizeof(rt_int16_t));
                break;
            case 'A':
                val = atoi((char *)recv_data.Data);
				angle = val;
                rt_sem_release(angle_sem);
                break;
            }
        }
    }
}
void CAN_Send_MSG(char *msg)
{
    CanTxMsg can_tx_msg;
    can_tx_msg.StdId = 0x51;
    can_tx_msg.ExtId = 0x00;
    can_tx_msg.IDE = CAN_ID_STD;
    can_tx_msg.RTR = CAN_RTR_DATA;
    //    while (*(msg + i) != '\0')
    //    {
    can_tx_msg.Data[0] = *(msg);
    //        i++;
    //    }
    can_tx_msg.DLC = 1;
    CAN_Transmit(CAN1, &can_tx_msg);
}
