#ifndef FSM_H
#define FSM_H

#include "state.h"

// farward declaration
typedef struct State State;

/* StateHandler is pointer to a func which takes an event as arg and returns next State */
/* typedef creates and alias so we can use statehandler later */
typedef State* (*StateHandler)(Event event);

// state node -> pointing to the individual state function and stateId
struct State {
	StateID id;
	StateHandler handler;
};

// current state of system
typedef struct{
	State *current;
} FSM;

// state machine initialize with initial state
void fsm_init(FSM *fsm, State *initial);

// dispatch state on event to trigger a transition
void fsm_dispatch(FSM *fsm, Event event);

#endif