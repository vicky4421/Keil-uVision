#ifndef BUTTON_H
#define BUTTON_H

#include "state.h"

void button_init(void);
void button_update(void);
EventID_t button_get_event(void);


#endif