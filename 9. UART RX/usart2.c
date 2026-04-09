#include "stm32f401xe.h"

#define GPIOA_PIN3 3
#define GPIOA_PIN2 2
#define APB1_CLK_FREQ 16000000
#define BAUD_RATE 115200
#define TXE (1U << 7)
#define RXNE (1U << 5)

static uint16_t compute_baud_rate(uint32_t clk_freq, uint32_t baud_rate);

void init_usart2(void){
	/* Enable clock for GPIOA*/
	RCC->AHB1ENR |= (1U << 0);
	
	/* Enable AF for GPIOA2*/
	GPIOA->MODER &= ~(3U << (2 * GPIOA_PIN2));
	GPIOA->MODER |= (2U << (2 * GPIOA_PIN2));
	
	/* Enable AF for GPIOA3*/
	GPIOA->MODER &= ~(3U << (2 * GPIOA_PIN3));
	GPIOA->MODER |= (2U << (2 * GPIOA_PIN3));    // 2U -> 10 (AF mode)
	
	/* Enable clock for USART2*/
	RCC->APB1ENR |= (1U << 17);
	
	/* Enable AF 7 for PA2*/
	GPIOA->AFR[0] &= ~(0xFU << (4 * GPIOA_PIN2));
	GPIOA->AFR[0] |= (7U << (4 * GPIOA_PIN2));
	
	/* Enable AF 7 for PA3*/
	GPIOA->AFR[0] &= ~(0xFU << (4 * GPIOA_PIN3));
	GPIOA->AFR[0] |= (7U << (4 * GPIOA_PIN3));		// 7U -> 0111
	
	/* Set Baud Rate */
	USART2->BRR = compute_baud_rate(APB1_CLK_FREQ, BAUD_RATE);
	
	/* Enable transmitter */
	USART2->CR1 |= (1U << 2);
	USART2->CR1 |= (1U << 3);
	USART2->CR1 |= (1U << 13);
}

static uint16_t compute_baud_rate(uint32_t clk_freq, uint32_t baud_rate){
	return (clk_freq + (baud_rate/2))/baud_rate;
}

char usart_receive_char(void){
    while(!(USART2->SR & RXNE)); // RXNE
    return USART2->DR;
}

void usart_send_char(char c){
	/* Wait TDR to be empty */
	while(!(USART2->SR & TXE));
	USART2->DR = c;
}

void usart_send_string(char *s){
	while(*s){
		usart_send_char(*s++);
	}
}
