#ifndef STATE_H
#define STATE_H

// id tracks current state of system
	typedef enum {
		STATE_ID_IDLE = 0,
		STATE_ID_RUNNING,
		STATE_ID_ERROR
	} StateID;

// defines the input that trigger changes between states.
	typedef enum {
		EVENT_NONE = 0,
		EVENT_SHORT_PRESS,
		EVENT_LONG_PRESS
	} Event;

#endif