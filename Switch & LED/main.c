#include "stm32f401xe.h"

void init_led(void){
	// Enable clock for onboard LED on port PA5
	RCC->AHB1ENR |= (1 << 0);
	
	// Disable analog and enable output
	// Reset and set Moder to 01
	GPIOA->MODER &= ~(3 << (2*5));
	GPIOA->MODER |= (1 << (2*5));
	
	// Blink LED for testing
//	while(1){
//		GPIOA->BSRR = (1 << 5);
//		for(volatile int i = 0; i < 100000; i++);
//		GPIOA->BSRR = (1 << (5 + 16));
//		for(volatile int i = 0; i < 100000; i++);
//	}
}

void init_switch(void){
	// Enable clock for onboard user push pull switch on port PC13
	RCC->AHB1ENR |= (1 << 2);
	
	// Disable analog and enable input
	// Clear bits to set Moder to 00
	GPIOC->MODER &= ~(3 << (2 * 13));
	
	// No need to set PUPDR (external pull-up already present on nucleo board)	
}


int main(){
	init_led();
	init_switch();
	
	while(1){
		// Read the switch
		if((GPIOC->IDR & (1<<13)) == 0){
			// button pressed turn on led
			GPIOA->BSRR = (1 << 5);
		} else {
			// turn off led
			GPIOA->BSRR = (1 << (5 + 16));
		}
	}
	
	return 0;
}