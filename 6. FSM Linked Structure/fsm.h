#ifndef FSM_H
#define FSM_H

#include "state.h"

typedef struct State State;

/* StateHandler is pointer to a func which takes an event as arg and returns a State pointer */
/* typedef creates and alias so we can use statehandler later */
typedef State* (*StateHandler)(Event event);

struct State {
	StateID id;
	StateHandler handler;
};

typedef struct{
	State *current;
} FSM;

void fsm_init(FSM *fsm, State *initial);
void fsm_dispatch(FSM *fsm, Event event);

#endif