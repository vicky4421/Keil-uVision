#ifndef STATE_H
#define STATE_H

	typedef enum {
		STATE_ID_IDLE = 0,
		STATE_ID_RUNNING,
		STATE_ID_ERROR
	} StateID;

	typedef enum {
		EVENT_NONE = 0,
		EVENT_SHORT_PRESS,
		EVENT_LONG_PRESS
	} Event;

#endif