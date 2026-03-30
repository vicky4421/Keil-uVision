#include "actions.h"
#include "systick.h"
#include "led.h"

#define RUNNING_BLINK_MS 500U
#define ERROR_BLINK_MS 200U

/* Internal system mode not system state */
typedef enum{
	MODE_IDLE = 0,
	MODE_RUNNING,
	MODE_ERROR
} System_mode_t;

static System_mode_t current_mode = MODE_IDLE;

static uint32_t last_toggle_time = 0;

void actions_init(void){
	current_mode = MODE_IDLE;
	last_toggle_time = systick_get_ms();
	
	led_set(LED_BLUE, LED_ON);
	led_set(LED_GREEN, LED_OFF);
	led_set(LED_RED, LED_OFF);
}

/*FSM entry actions*/
void action_idle(void){
	current_mode = MODE_IDLE;
	
	led_set(LED_BLUE, LED_ON);
	led_set(LED_GREEN, LED_OFF);
	led_set(LED_RED, LED_OFF);
}
	
void action_running(void){
	current_mode = MODE_RUNNING;
	
	/* reset toggle time */
	last_toggle_time = systick_get_ms();
	
	/* Initial LED state */
    led_set(LED_BLUE, LED_OFF);
    led_set(LED_RED, LED_OFF);
    led_set(LED_GREEN, LED_OFF);
}
	
void action_error(void){
	current_mode = MODE_ERROR;

    /* Reset timing */
    last_toggle_time = systick_get_ms();

    /* Initial LED state */
    led_set(LED_BLUE, LED_OFF);
    led_set(LED_GREEN, LED_OFF);
    led_set(LED_RED, LED_OFF);
}

void actions_update(void){
	uint32_t now = systick_get_ms();
	
	switch(current_mode){
		case MODE_IDLE:
			break;
		case MODE_RUNNING:
			if((now - last_toggle_time) >= RUNNING_BLINK_MS){
				last_toggle_time = now;
				led_toggle(LED_GREEN);
			}
			break;
		case MODE_ERROR:
			if((now - last_toggle_time) >= ERROR_BLINK_MS){
				last_toggle_time = now;
				led_toggle(LED_RED);
			}
			break;
		default:
			break;
	}
}