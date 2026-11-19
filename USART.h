#ifndef __STM32L476R_NUCLEO_USART_H
#define __STM32L476R_NUCLEO_USART_H
#include "stm32l476xx.h"
#include "clock.h"

#define BufferSize  8

void USART_Init(USART_TypeDef * USARTx);
void USART_Write(USART_TypeDef * USARTx, uint8_t * buffer, int nBytes);
void USART_Read(USART_TypeDef * USARTx, uint8_t * buffer, int nBytes);
void receive(USART_TypeDef *USARTx, uint8_t *buffer,volatile uint32_t *pCounter);
void USART2_IRQHandler(void);
void setModer(GPIO_TypeDef * port, uint32_t pin, unsigned char mode);

	
#endif