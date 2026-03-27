#include "fsm.h"
#include "led.h"

extern State state_running;
extern State state_error;
	
extern State state_idle;

static State* idle_handler(Event event){
	
	/* State Behaviour */
	led_set(LED_BLUE, LED_ON);
	led_set(LED_GREEN, LED_OFF);
	led_set(LED_RED, LED_OFF);
	
	/* Event handling */
	switch(event){
		case EVENT_SHORT_PRESS:
			return &state_running;
		
		case EVENT_LONG_PRESS:
			return &state_error;
		
		case EVENT_NONE:
		
		default:
			return &state_idle;
	}
}

State state_idle = {
	.id = STATE_ID_IDLE,
	.handler = idle_handler
};