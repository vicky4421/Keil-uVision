#ifndef LED_H
#define LED_H

typedef enum{
	LED_OFF = 0,
	LED_ON
} LedState;

typedef enum{
	LED_BLUE = 0,
	LED_GREEN,
	LED_RED
} LedID;

void led_init(void);
void led_set(LedID id, LedState state);
void led_toggle(LedID id);

#endif