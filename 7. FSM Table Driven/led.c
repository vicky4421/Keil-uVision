#include "led.h"
#include "stm32f401xe.h"

#define LED_COUNT (sizeof(led_map) / sizeof(led_map[0]))		// 3

typedef struct{
	GPIO_TypeDef *port;				// already defined: GPIO_TypeDef in cmsis
	uint8_t pin;
} LedHW;

// array of type LedHW
// lookup table for LEDs and its corresponding pins
static const LedHW led_map[] = {
	[LED_BLUE] = {GPIOA, 5},
	[LED_GREEN] = {GPIOA, 6},
	[LED_RED] = {GPIOA, 7}
};

void led_init(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;		// enable gpioa clock
	
	/* Configure pin as output */
	for(unsigned int i = 0; i < LED_COUNT; i++){
		uint8_t pin = led_map[i].pin;
		
		/* set output mode to 01 */
		led_map[i].port->MODER &= ~(3U << (2 * pin));
		led_map[i].port->MODER |= (1U << (2 * pin));
	}
}

void led_set(LedID id, LedState state){
	if(id >= LED_COUNT) return;
	
	GPIO_TypeDef *port = led_map[id].port;
	uint8_t pin = led_map[id].pin;
	
	if(state == LED_ON) port->BSRR = (1U << pin);    // set pin
	else port->BSRR = (1U << (pin + 16));						// reset pin
	
}

void led_toggle(LedID id){
	if(id >= LED_COUNT) return;
	GPIO_TypeDef *port = led_map[id].port;
	uint8_t pin = led_map[id].pin;
	
	if (port->ODR & (1U << pin)) port->BSRR = (1U << (pin + 16));
	else port->BSRR = (1U << pin);
}