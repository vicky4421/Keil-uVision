#ifndef STATE_H
#define STATE_H

typedef enum{
	STATE_IDLE = 0,
	STATE_RUNNING,
	STATE_ERROR,
	STATE_MAX
} StateID_t;

typedef enum{
	EVENT_NONE = 0,
	EVENT_SHORT_PRESS,
	EVENT_LONG_PRESS,
	EVENT_MAX
} EventID_t;

#endif