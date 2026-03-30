#include "fsm.h"
#include "state.h"
#include "fsm_table.h"

void fsm_init(FSM_t *fsm, State_t initial_state){
	if(fsm == 0) return;
	fsm->current_state = initial_state;
}

void fsm_dispatch(FSM_t *fsm, Event_t event){
	if(fsm == 0) return;
	if(event >= EVENT_MAX) return;
	
	/* after receiving an event, it iterates through the fsm table */
	for(uint32_t i = 0; i < fsm_table_size; i++ ){
		
		/* look for current state and event in table that are matches to system current state and event */
		if((fsm_table[i].current == fsm->current_state) && (fsm_table[i].event == event) ){
			
			/* if match found executes the action from the table */
			/* execute actioin */
			if(fsm_table[i].action != 0) fsm_table[i].action();
			
			/* updates the state of the system */
			fsm->current_state = fsm_table[i].next;
			
			return;
		}
	}
	
}