#include "usart2.h"

int main(void){
	
	init_usart2();
	
//	usart_send_char('H');
//	usart_send_char('e');
//	usart_send_char('l');
//	usart_send_char('l');
//	usart_send_char('o');
//	usart_send_char('\x20');
//	usart_send_char('W');
//	usart_send_char('o');
//	usart_send_char('r');
//	usart_send_char('l');
//	usart_send_char('d');
//	usart_send_char('!');
	
	usart_send_string("Hello World \r\n");
	
	while(1);
	
	return 0;
}