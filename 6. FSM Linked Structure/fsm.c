#include "fsm.h"

void fsm_init(FSM *fsm, State *initial){
	if(fsm == 0 || initial == 0) return;
	
	fsm->current = initial;
}

void fsm_dispatch(FSM *fsm, Event event){
	if(fsm == 0 || fsm->current == 0) return;
		
		/* Call current state's handler */
		State *next = fsm->current->handler(event);
		
		/* handler must return a valid state */
		if(next != 0) fsm->current = next;
}