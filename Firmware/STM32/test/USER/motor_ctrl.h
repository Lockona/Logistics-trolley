#include "stm32f10x.h"
#include "rtthread.h"
//struct position_pid
//{
//    float KP;
//    float KI;
//    float KD;
//    float old_error;
//    float new_error;
//    float sum_error;
//};
struct Inc_pid
{
    float KP;
    float KI;
    float KD;
    float prev_error;
    float last_error;
    float new_error;
}; 

extern struct Inc_pid r_pid_val;
extern struct Inc_pid l_pid_val;
extern rt_int16_t expect_speed;
extern rt_uint16_t angle;

void MOTOR_PWM_Init(void);
void MOTOR_GPIO_Init(void);
void stop(void);
void wheel_ctrl_task(void *param);
void setAngle(void *param);
