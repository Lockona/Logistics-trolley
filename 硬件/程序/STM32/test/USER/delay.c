#include "delay.h"
#include "rtthread.h"

void delay_ms(uint32_t ms)
{
	uint32_t t = 0;
	t = rt_tick_get() + ms;
	while ((int32_t)(t - rt_tick_get()) > 0)
		;
}
