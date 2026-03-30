#ifndef FSM_H
#define FSM_H

#include <stdint.h>

typedef uint8_t State_t;
typedef uint8_t Event_t;

typedef void (*Action_t)(void);

/*
	Machine is in "current" state, if specific "event" happens it should move to "next" state and execute an "action"
*/
typedef struct{
	State_t current;
	Event_t event;
	State_t next;
	Action_t action;
} Transition_t;

// track current state of system.
typedef struct{
	State_t current_state;
} FSM_t;

void fsm_init(FSM_t *fsm, State_t initial_state);

void fsm_dispatch(FSM_t *fsm, Event_t event);

#endif