#include "stm32f401xe.h"

int main(void)
{
    // RCC->AHB1ENR |= (1 << 0);        // enable GPIOA clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~(3 << (2*5));   // clear PA5 mode
    GPIOA->MODER |=  (1 << (2*5));   // set PA5 as output

    

    while(1){
		GPIOA->BSRR = (1 << 5);          // set PA5 HIGH
		for(volatile int i = 0; i < 200000; i++);
		GPIOA->BSRR = (1 << (5 + 16));
		for(int i = 0; i < 50000; i++);
	}
}