#ifndef USART2_H
#define USART2_H

void init_usart2(void);
char usart_receive_char(void);
void usart_send_char(char c);
void usart_send_string(char *s);

#endif