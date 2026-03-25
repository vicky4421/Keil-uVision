	/*
		Finite State Machine
		Multi-Mode Device Controller
	*/
	#include "stm32f401xc.h"
	#include "state.h"
	#include "led.h"
	#include "button.h"

	#define SYSCLK 16000000

	volatile uint32_t ticks = 0;

	uint8_t green_led_state = 0;
	uint8_t red_led_state = 0;
	uint32_t last_green = 0;
	uint32_t last_red = 0;

	State current_state = STATE_IDLE;
	State prev_state = (State)(-1);         // no -1 state in State enum, first time state setup

	void init_systick(void){
		/*
			Calculate RELOAD
			reload = (clock * delay) - 1
			reload = (16000000 * 0.001) - 1 = 16000 - 1
		*/
		
		/*Configure SysTick*/
		SysTick->CTRL = 0;
		SysTick->LOAD = (SYSCLK / 1000) - 1;
		SysTick->VAL = 0;
		SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
	}

	/* Define SysTick Handler */
	void SysTick_Handler(void){
		ticks++;
	}

	/* Handle event */
	void handle_event(Event e){
		switch(current_state){
			case STATE_IDLE:
				if(e == EVENT_SHORT_PRESS) current_state = STATE_RUNNING;
				else if(e == EVENT_LONG_PRESS) current_state = STATE_ERROR;
				break;
			case STATE_RUNNING:
				if(e == EVENT_SHORT_PRESS) current_state = STATE_IDLE;
				else if(e == EVENT_LONG_PRESS) current_state = STATE_ERROR;
				break;
			case STATE_ERROR:
				if(e == EVENT_SHORT_PRESS) current_state = STATE_RUNNING;
				else if(e == EVENT_LONG_PRESS) current_state = STATE_IDLE;
				break;
			default:
				break;
		}
	}

	int main(void){
		init_led_pins();
		init_button();
		init_systick();
		
		while(1){
			uint32_t now = ticks;
			Event e = detect_event();
			
			// ONLY handle the event if it's not "None"
			if (e != EVENT_NONE) { 
        handle_event(e);
			}
			
			if(current_state != prev_state){
				switch(current_state){
					case STATE_IDLE:
						led_blue_on();
						led_green_off();
						led_red_off();
						break;
					case STATE_RUNNING:
						led_blue_off();
						led_red_off();
						green_led_state = 0;
						red_led_state = 0;
						last_green = now;				// reset timer for green led -> state initiated
						break;
					case STATE_ERROR:
						led_blue_off();
						led_green_off();
						red_led_state = 0;
						green_led_state = 0;
						last_red = now;         // reset timer for red led -> state initiated
						break;
					default:
						break;
				}
				prev_state = current_state;
			}
			
			/* STATE RUNNING -> BLINK GREEN LED (SLOW) */
			if(current_state == STATE_RUNNING){
				if((now - last_green) >= 500){
					last_green = now;							// reset timer for next 500ms cycle
					if(green_led_state){
						led_green_off();
						green_led_state = 0;
					} else {
						led_green_on();
						green_led_state = 1;
					}
				}
			}
			
			/*STATE ERROR -> BLINK RED LED (FAST)*/
			else if(current_state == STATE_ERROR){
				if(now - last_red >= 200){
							last_red = now;						// reset timer for next 500ms cycle
							if(red_led_state){
									led_red_off();
									red_led_state = 0;
							} else {
									led_red_on();
									red_led_state = 1;
							}
					}
			}
		}
		
		return 0;
	}