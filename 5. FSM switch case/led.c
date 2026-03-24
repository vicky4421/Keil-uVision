#include "stm32f401xc.h"
#include "led.h"

#define LED_BLUE_PIN 5
#define LED_GREEN_PIN 6
#define LED_RED_PIN 7
#define PIN_RESET_OFFSET 16

// initialize pins for leds
void init_led_pins(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;																																					// enable clock for port A
	GPIOA->MODER &= ~((3 << (2 * LED_BLUE_PIN)) | (3 << (2 * LED_GREEN_PIN)) | (3 << (2 * LED_RED_PIN)));					// clear moder bits
	GPIOA->MODER |= (1 << (2 * LED_BLUE_PIN)) | (1 << (2 * LED_GREEN_PIN)) | (1 << (2 * LED_RED_PIN));						// set bits for output 01
}

void led_blue_on(void){
	GPIOA->BSRR = (1 << LED_BLUE_PIN);
}

void led_blue_off(void){
	GPIOA->BSRR = (1 << (LED_BLUE_PIN + PIN_RESET_OFFSET));
}

void led_green_on(void){
	GPIOA->BSRR = (1 << LED_GREEN_PIN);
}

void led_green_off(void){
	GPIOA->BSRR = (1 << (LED_GREEN_PIN + PIN_RESET_OFFSET));
}

void led_red_on(void){
	GPIOA->BSRR = (1 << LED_RED_PIN);
}

void led_red_off(void){
	GPIOA->BSRR = (1 << (LED_RED_PIN + PIN_RESET_OFFSET));
}