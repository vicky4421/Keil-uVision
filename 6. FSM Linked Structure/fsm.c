#include "fsm.h"

// safety check of pointer and sets the initial state of system
void fsm_init(FSM *fsm, State *initial){
	if(fsm == 0 || initial == 0) return;
	
	fsm->current = initial;
}

// executes the handler func of current state and updates new state returned by handler.
// if handler returns null/0, system stays in current state
void fsm_dispatch(FSM *fsm, Event event){
	if(fsm == 0 || fsm->current == 0) return;
		
		/* Call current state's handler */
		State *next = fsm->current->handler(event);
		
		/* handler must return a valid state */
		if(next != 0) fsm->current = next;
}