#ifndef BUTTON_H
#define BUTTON_H

#include "state.h"
#include "led.h"

void init_button(void);
Event detect_event(void);

#endif