/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "main.h"
#include "can.h"
#include "delay.h"
#include "encoder.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

void USART1_IRQHandler(void)
{
  //  uint8_t ret;
  if (USART1->SR & USART_FLAG_RXNE)
  {
    //	ret = USART1->DR;
    //	while(!(USART1->SR&(0x01<<7)));
    //	USART1->DR = ret;
  }
  USART1->SR &= ~USART_FLAG_RXNE;
}

void CAN1_RX1_IRQHandler(void)
{
  CAN_Receive(CAN1, CAN_FIFO1, &recv_data);
  if (recv_data.DLC)
  {
    rt_sem_release(can_recv_sem);
  }
}
static uint8_t catch_time = 0;
void TIM1_UP_IRQHandler(void)
{
  if (TIM1->SR & 0x01)
  {
    catch_time++;
    if (catch_time == 10)
    {
      catch_time = 0;
      L_Pulse = TIM2->CNT;
      R_Pulse = TIM3->CNT;
		L_Pulse = (L_Pulse>0)?(L_Pulse):(L_Pulse*-1);
		R_Pulse = (R_Pulse>0)?(R_Pulse):(R_Pulse*-1);
      TIM2->CNT = 0;
      TIM3->CNT = 0;
      rt_sem_release(wheel_flag_sem);
    }
  }
  TIM1->SR &= ~(0x01);
}
void TIM2_IRQHandler(void)
{
  if (TIM2->SR & 0x01)
  {
  }
  TIM2->SR &= ~(0x01);
}
void TIM3_IRQHandler(void)
{
  if (TIM3->SR & 0x01)
  {
  }
  TIM3->SR &= ~(0x01);
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
