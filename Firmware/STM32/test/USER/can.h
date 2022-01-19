#include "stm32f10x.h"

extern CanRxMsg recv_data;

void Can_Init(void);
void can_recv_to_ctrl(void *param);
void CAN_Send_MSG(char *msg,uint8_t len);
