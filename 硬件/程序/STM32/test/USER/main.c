#include <stdio.h>
//#include "rtthread.h"
#include "stm32f10x.h"
#include "main.h"
#include "delay.h"
#include "motor_ctrl.h"
#include "usart1.h"
#include "encoder.h"
#include "oled_SPI.h"
#include "can.h"

rt_sem_t wheel_flag_sem = RT_NULL;
rt_sem_t can_recv_sem = RT_NULL;
rt_sem_t angle_sem = RT_NULL;
rt_mq_t speed_mq = RT_NULL;
rt_thread_t wheel_task = RT_NULL;
rt_thread_t setAngle_task = RT_NULL;
rt_thread_t can_recv_task = RT_NULL;

int main()
{
	rt_enter_critical();
//	sr04_Init();
	wheel_flag_sem = rt_sem_create("wheel_flag", 0, RT_IPC_FLAG_FIFO);
	can_recv_sem = rt_sem_create("can_rcv", 0, RT_IPC_FLAG_FIFO);
	angle_sem = rt_sem_create("angle", 0, RT_IPC_FLAG_FIFO);
	speed_mq = rt_mq_create("speed", sizeof(rt_uint16_t), 10, RT_IPC_FLAG_FIFO);

	can_recv_task = rt_thread_create("can_rcv_thread", can_recv_to_ctrl, RT_NULL, 1024, 5, 20);
	wheel_task = rt_thread_create("wheel_task", wheel_ctrl_task, RT_NULL, 1024, 7, 20);
	setAngle_task = rt_thread_create("setAngle", setAngle, RT_NULL, 1024, 6, 20);
	if (can_recv_task != RT_NULL)
	{
		rt_thread_startup(can_recv_task);
	}
	if (wheel_task != RT_NULL)
	{
		rt_thread_startup(wheel_task);
	}
	if (setAngle_task != RT_NULL)
	{
		rt_thread_startup(setAngle_task);
	}
	rt_exit_critical();
	while (1)
	{
		//		sprintf(buf, "%d", i);
//		get_distan();
		rt_thread_delay(500);
		//		CAN_Send_MSG(&i);
		//		CAN_Receive(CAN1,CAN_FIFO1,&data);
	}
}
