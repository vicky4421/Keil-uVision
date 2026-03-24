#ifndef STATE_H
#define STATE_H

	typedef enum {
		STATE_IDLE,
		STATE_RUNNING,
		STATE_ERROR
	} State;

	typedef enum {
		EVENT_NONE,
		EVENT_SHORT_PRESS,
		EVENT_LONG_PRESS
	} Event;

#endif