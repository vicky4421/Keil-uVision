#include "stm32f401xe.h"

#include "led.h"
#include "button.h"
#include "systick.h"
#include "fsm.h"
#include "actions.h"
#include "state.h"

int main(void){

	systick_init();
	led_init();
	button_init();
	actions_init();
	
	FSM_t fsm;
	fsm_init(&fsm, STATE_IDLE);
	
	while(1){
		button_update();
		
		EventID_t event = button_get_event();
		
		if(event != EVENT_NONE) fsm_dispatch(&fsm, event);
		
		actions_update();
	}
	
	return 0;
}