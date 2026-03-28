#include "button.h"
#include "stm32f401xc.h"
#include "systick.h"
#include "led.h"

#define PUSH_SWITCH_PIN 13
#define DEBOUNCE_MS 50
#define LONG_PRESS_MS 1000

static uint8_t last_stable = 1;
static uint8_t last_read = 1;

static uint32_t last_debounce_time = 0;
static uint32_t press_start_time = 0;

static Event button_event = EVENT_NONE;

void button_init(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &= ~(3 << (2 * PUSH_SWITCH_PIN));
}

void button_update(void){
	
	uint32_t now = systick_get_ms();
	
	/* Read raw button state */
	uint8_t reading = (GPIOC->IDR & (1 << PUSH_SWITCH_PIN)) ? 1 : 0;
	
	/* Detect change (for debounce) */
	if(reading != last_read){
		last_debounce_time = now;
		last_read = reading;
	}
	
	/* If button is stable after debounce time */
	if((now - last_debounce_time) >= DEBOUNCE_MS){
		/* State changed */
		if(reading != last_stable){
			last_stable = reading;
			
			/* Button pressed (active LOW) */
			if(reading == 0) press_start_time = now;
			
			/* Button released */
			else {
				uint32_t press_time = now - press_start_time;
				if(press_time > LONG_PRESS_MS) button_event = EVENT_LONG_PRESS;
				else button_event = EVENT_SHORT_PRESS;
			}
		}
	}
}

Event button_get_event(void){
	Event e = button_event;
	button_event = EVENT_NONE;
	return e;
}