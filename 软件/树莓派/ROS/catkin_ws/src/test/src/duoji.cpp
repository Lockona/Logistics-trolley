#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>
#include "test/duoji.h"

#define pwm_pin 26
int success = -1;
int duoji_Init()
{
    if (wiringPiSetup() < 0)
    {
        perror("wiringPi");
        return success;
    }
    success = 0;
    pinMode(pwm_pin, PWM_OUTPUT);
    pwmSetClock(384); //pwm_Hz = 19.2MHz/1000/384 = 50Hz
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(1000);
    pwmWrite(pwm_pin, 25);
    return success;
}
void duoji_run(int val)
{
    if (success < 0)
    {
        printf("舵机未初始化!!!\n");
        return;
    }
    pwmWrite(pwm_pin, val);
}