#include "usart2.h"

int main(void){
	
	init_usart2();
	
	usart_send_string("USART READY! \0X20 \r\n");
	
	while(1){
		char c = usart_receive_char();
		usart_send_char(c);
	}
	
	return 0;
}