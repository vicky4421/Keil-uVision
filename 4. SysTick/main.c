// SysTick Timer Configuration for LED Blinking for 84 MHz(max)

#include "stm32f401xc.h"

#define SYSCLK 84000000

volatile uint32_t ticks = 0;
volatile uint32_t last = 0;

// Enable PLL to work with STM32F401RET6 with 84MHZ
void init_pll(void){
	
	// Enable HSE (External Crystal)
	RCC->CR |= (1 << 16);
	
	// Wait until HSE ready
	while(!(RCC->CR & (1 << 17)));
		
	// Configure PLL
	/*
			PLLM = 8   ? 8 / 8 = 1 MHz (valid input)
			PLLN = 168 ? 1 × 168 = 168 MHz (valid VCO range)
			PLLP = 2   ? 168 / 2 = 84 MHz
	*/
	RCC->PLLCFGR = 
		(8 << 0) | 		//PLLM -> 8/8 = 1
		(168 << 6) |  //PLLN -> 1 X 168 = 168
		(0 << 16) |		//PLLP -> 00 FOR 2
		(1 << 22);		//PLL source (1 for HSE)
		
	// Enable PLL
	RCC->CR |= (1 << 24);
		
	// Wait until PLL ready
	while(!(RCC->CR & (1 << 25)));
	
	// Configure Flash Latency -> 60 < hclk < 84 -> 2 wait state
	FLASH->ACR |= (2 << 0);
	
	// Switch System Clock to PLL -> 10 for PLL
	RCC->CFGR &= ~(3 << 0);
	RCC->CFGR |=  (2 << 0);
	
	// Verify Clock swithed to PLL
	// First read system watch state(sws0, sws1) and compare it to state 10
	// wait if not equal to 10
	while((RCC->CFGR & (3 << 2)) != (2 << 2));
}

void init_systick(void){
	/*
		Calculate RELOAD
		reload = (clock * delay) - 1
		reload = (84000000 * 0.001) - 1 = 84000 - 1
	*/
	
	// Configure SysTick
	SysTick->CTRL = 0;
	SysTick->LOAD = (SYSCLK / 1000)-1;		// set relaod
	SysTick->VAL = 0;
	//SysTick->CTRL = (1 << 2) | (1 << 1) | (1 << 0);
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

// define handler
void SysTick_Handler(void){
	ticks++;
}

// configure pin PA5
void init_PA5(void){
	RCC->AHB1ENR |= (1 << 0);        // enable GPIOA clock;
  GPIOA->MODER &= ~(3 << (2*5));   // clear PA5 mode
  GPIOA->MODER |=  (1 << (2*5));   // set PA5 as output
}

int main(){
	init_pll();
	init_systick();
	init_PA5();
	
	while(1){
		if((ticks - last) >= 500){
			GPIOA->ODR ^= (1 << 5);
			last = ticks;
		}
	}
	
	return 0;
}