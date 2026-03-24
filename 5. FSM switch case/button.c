#include "stm32f401xc.h"
#include "button.h"

#define PUSH_SWITCH_PIN 13		// PC13

extern volatile uint32_t ticks;

static uint8_t prev_state = 0;
static uint32_t press_time = 0;

// initialize button
void init_button(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;																																		// enable clock for port C
	GPIOC->MODER &= ~(3 << (2 * PUSH_SWITCH_PIN));																													// clear moder bits	
}

int button_pressed(void){
	return !(GPIOC->IDR & (1 << PUSH_SWITCH_PIN));
}

/* Detect button pressed event*/
Event detect_event(void){

	uint8_t current_state = button_pressed();
	
	if(current_state && !prev_state) press_time = ticks;		// button is just pressed, start counting time 1 && !0
	else if(!current_state && prev_state){									// button is released, measure time !0 && 1
		uint32_t duration = ticks - press_time;
		if (duration > 1000){
			prev_state = current_state;
			return EVENT_LONG_PRESS;
		}																											// return long press event if ticks are more than 1000
		else if (duration > 100 && duration <= 1000){
			prev_state = current_state;
			return EVENT_SHORT_PRESS;
		}         																						// return short press event if ticks are less than 1000 (ignore less than 50)
						
	}
	prev_state = current_state;
	return EVENT_NONE;
}