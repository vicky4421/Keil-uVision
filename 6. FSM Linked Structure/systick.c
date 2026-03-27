#include "systick.h"
#include "stm32f401xc.h"

#define SYSCLK 16000000

static volatile uint32_t ticks = 0;

void systick_init(){
	SysTick->CTRL = 0;
	SysTick->LOAD = (SYSCLK / 1000) - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void){
		ticks++;
}

uint32_t systick_get_ms(void){
	return ticks;
}