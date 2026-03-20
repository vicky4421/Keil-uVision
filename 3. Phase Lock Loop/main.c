// Enable PLL to work with STM32F401RET6 with 84MHZ

#include "stm32f401xc.h"

void init_pll(void){
	// Enable HSE (External Crystal)
	RCC->CR |= (1 << 16);
	
	// Wait until HSE ready
	while(!(RCC->CR & (1 << 17)));
		
	// Configure PLL
	/*
			PLLM = 8   -> 8 / 8 = 1 MHz (valid input)
			PLLN = 168 -> 1 × 168 = 168 MHz (valid VCO range)
			PLLP = 2   -> 168 / 2 = 84 MHz
	*/
	RCC->PLLCFGR = 
		(8 << 0) | 		// PLLM -> 8/8 = 1
		(168 << 6) |  // PLLN -> 1 X 168 = 168
		(0 << 16) |		// PLLP -> 00 FOR 2
		(1 << 22);		// PLL source (1 for HSE)
		
	// Enable PLL
	RCC->CR |= (1 << 24);
		
	// Wait until PLL ready
	while(!(RCC->CR & (1 << 25)));
	
	// Configure Flash Latency -> 60 < hclk < 84 -> 2 wait state
	FLASH->ACR |= (2 << 0);
	
	// Switch System Clock to PLL -> 10 for PLL
	RCC->CFGR |= (2 << 0);
	
	// Verify Clock swithed to PLL
	// First read system watch state(sws0, sws1) and compare it to state 10
	// wait if not equal to 10
	while((RCC->CFGR & (3 << 2)) != (2 << 2));
}

int main(){
	init_pll();
	return 0;
}