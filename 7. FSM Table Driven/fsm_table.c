#include "actions.h"
#include "fsm.h"
#include "state.h"

const Transition_t fsm_table[] = {
	/* IDLE -> RUNNING */
	{ STATE_IDLE, EVENT_SHORT_PRESS, STATE_RUNNING, action_running },
	
	/* RUNNING -> IDLE */
	{ STATE_RUNNING, EVENT_SHORT_PRESS, STATE_IDLE, action_idle },
	
	/* IDLE/RUNNING -> ERROR */
	{ STATE_IDLE, EVENT_LONG_PRESS, STATE_ERROR, action_error },
	{ STATE_RUNNING, EVENT_LONG_PRESS, STATE_ERROR, action_error },
	
	/* ERROR -> IDLE/RUNNING */
	{ STATE_ERROR, EVENT_LONG_PRESS, STATE_IDLE, action_idle },
	{ STATE_ERROR, EVENT_SHORT_PRESS, STATE_RUNNING, action_running },
};

const uint32_t fsm_table_size = sizeof(fsm_table) / sizeof(fsm_table[0]);