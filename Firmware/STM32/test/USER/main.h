#include "rtthread.h"

extern rt_sem_t wheel_flag_sem;
extern rt_sem_t can_recv_sem;
extern rt_sem_t angle_sem;
extern rt_mq_t speed_mq;

extern int16_t ce_time;

void sr04_Init(void);
void get_distan(void);
