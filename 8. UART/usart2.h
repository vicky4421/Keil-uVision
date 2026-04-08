#ifndef USART2_H
#define USART2_H

#include "stm32f401xe.h"

void init_usart2(void);
void usart_send_char(char c);
void usart_send_string(char *s);

#endif