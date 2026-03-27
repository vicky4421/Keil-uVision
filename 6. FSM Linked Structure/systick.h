#ifndef SYSTICK_H
#define SYSTICK_H
#include <stdint.h>

/* Initialize systick for 1ms tick */
void systick_init();

void SysTick_Handler(void);

/* Get system time in ms */
uint32_t systick_get_ms(void);

#endif