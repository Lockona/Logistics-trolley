#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h>

#define pwm_pin 26
#define key_pin 28

char flag = 0;

void call_back()
{
    if (digitalRead(key_pin) == 0)
    {
        delay(10);
        if (digitalRead(key_pin) == 0)
        {
            flag = 1;
        }
    }
}
void my_handle()
{
    flag = 1;
}

int main()
{
    printf("Hello World!!!\n");
    if (wiringPiSetup() < 0)
    {
        perror("wiringPi");
        return -1;
    }
    signal(SIGINT, my_handle);
    pinMode(pwm_pin, PWM_OUTPUT);
    pwmSetClock(384); //pwm_Hz = 19.2MHz/1000/384 = 50Hz
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(1000);
    pwmWrite(pwm_pin, 75);
    pinMode(key_pin, INPUT);
    pullUpDnControl(key_pin, PUD_UP);
    if (wiringPiISR(key_pin, INT_EDGE_FALLING, &call_back) < 0)
    {
        perror("ISR");
        return -1;
    }
    int i = 75;
    while (1)
    {
        if (flag == 1)
        {
            if (i == 75)
            {
                i = 25;
            }
            else
            {
                i = 75;
            }
            printf("pressed!!! %d\n", i);
            flag = 0;
            pwmWrite(pwm_pin, i);
        }
        delay(100);
    }
}