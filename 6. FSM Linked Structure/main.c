#include "stm32f401xc.h"
#include "led.h"
#include "button.h"
#include "systick.h"
#include "fsm.h"

extern State state_idle;

int main(){
	led_init();
	button_init();
	systick_init();
	
	FSM fsm;
	fsm_init(&fsm, &state_idle);
	
	while(1){
		button_update();
		Event e = button_get_event();
		if(e != EVENT_NONE) fsm_dispatch(&fsm, e);
		fsm_dispatch(&fsm, EVENT_NONE);
	}
	return 0;
}