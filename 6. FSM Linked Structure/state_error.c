#include "fsm.h"
#include "led.h"
#include "systick.h"

extern State state_idle;
extern State state_running;
extern State state_error;

static uint32_t last_toggle_time = 0;
static uint8_t led_state = 0;

static State* error_handler(Event event){
	uint32_t now = systick_get_ms();
	
	led_set(LED_BLUE, LED_OFF);
	led_set(LED_GREEN, LED_OFF);
	
	if((now - last_toggle_time) >= 200){
		last_toggle_time = now;
		
		led_state ^= 1;
		led_set(LED_RED, led_state ? LED_ON : LED_OFF);
	}
	
	switch(event){
		case EVENT_SHORT_PRESS:
			led_state = 0;
			last_toggle_time = now;
			return &state_idle;
		case EVENT_LONG_PRESS:
			led_state = 0;
			last_toggle_time = now;
			return &state_running;
		case EVENT_NONE:
		default:
			return &state_error;
	}
}

State state_error = {
	.id = STATE_ID_ERROR,
	.handler = error_handler
};