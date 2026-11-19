#include "stm32l476xx.h"
#include "USART.h"



uint8_t USART2_Buffer_Rx[BufferSize]; 
volatile uint32_t Rx2_Counter = 0; 


//Initialize GPIO for USART
void USART_Init(USART_TypeDef * USARTx){
	setUpClock('A');
	
	//RCC->APB2ENR |= RCC_APB1ENR1_USART2EN; // Enable UART 2 Clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;

	// Select system clock (SYSClK) USART clock source of UART2
	// 00 = PCLK, 01 = System clock (SYSCLK), 
	// 10 = HSI16, 11 = LSE
	RCC->CCIPR &= ~(RCC_CCIPR_USART2SEL); 
	RCC->CCIPR |= (RCC_CCIPR_USART2SEL_0);
	
	setModer(GPIOA, 2, 'F');
	setModer(GPIOA, 3, 'F');
	
	GPIOA->AFR[0] &= ~(0xFFU << (4*2));   // clear AFSEL2 and AFSEL3
	GPIOA->AFR[0] |=  (0x77U << (4*2));   // AF7 = USART2 on PA2 (TX) / PA3 (RX)
	//GPIOA->AFR[0] |= ~(0x77 << (4*2));//Set pin PA2 and PA3 to AF7
	
	GPIOA->OSPEEDR |= 0xF << (2*2);
	GPIOA->PUPDR &= ~(0xF<<(2*2));
	GPIOA->PUPDR |= 0x5<<(2*2);//Select pull-up
	GPIOA->OTYPER &= ~(0x3<<2);
		
	// Diable USART
	USARTx->CR1 &= ~USART_CR1_UE; 
	
	// Set data Length to 8 bits 
	// 00 = B data bits, 01 = 9 data bits, 10 = 7 data bits 
	USARTx->CR1 &= ~USART_CR1_M;
	
	//Set parity control as no parity
	// 0 = no parity, 
	// 1 = parity enabled (then, program PS bit to select Even or Odd parity) 
	USARTx->CR1 &= ~USART_CR1_PCE; 
	
	// Oversampling by 16 
	// 0 =oversampling by 16, 1 =oversampling by 8 
	USARTx->CR1 &= ~USART_CR1_OVER8; 
	
	
	// Set Baud rate to 9600 using APB frequency (Be MHz) 
	// See Example 1 in Section 22.1.2 
	USARTx->BRR = 0x1A0;
	
	// Enable transmission and reception 
	USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE); 
	
	//Enable USART 
	USARTx->CR1 |= USART_CR1_UE; 
	
	// Verify that USART is ready for transmission 
	// TEACK: Transmit enable acknowledge flag. Hardware sets or resets it. 
	while ((USARTx->ISR & USART_ISR_TEACK) == 0); 
	
	// Verify that USART is ready for reception 
	// REACK: Receive enable acknowledge flag. Hardware sets or resets it. 
	while ((USARTx->ISR & USART_ISR_REACK) == 0); 

	// This Enables the interrupt
	// for now dont enable
	//USARTx->CR1 |= USART_CR1_RXNEIE;
	//NVIC_SetPriority(USART2_IRQn, 1);
	//NVIC_EnableIRQ(USART2_IRQn);

}


void USART_Write(USART_TypeDef * USARTx, uint8_t * buffer, int nBytes) {
	int i;
	for (i = 0; i < nBytes; i++)
	{
		while (!(USARTx->ISR & USART_ISR_TXE)); // wait until TXE (TX empty) is set
		USARTx->TDR = (buffer[i] & 0x1FF);     // Writing USART_DR automatically clears the TXE flag
	}
	while (!(USARTx->ISR & USART_ISR_TC)); // wait until TC bit is set
	USARTx->ICR = USART_ICR_TCCF;
}

void USART_Read(USART_TypeDef * USARTx, uint8_t * buffer, int nBytes)
{
	int i;
	for (i=0;i< nBytes; i++)
	{
		while (!(USARTx->ISR & USART_ISR_RXNE)); // wait
		buffer[i] = USARTx -> RDR;       // reading RDR clears RXNE
	}
}

//Recieving data
/*
void USART2_IRQHandler(USART2_TypeDef * USART2x, uint8_t * buffer, uint8_t * pRx_counter){
if(USART2x->SR & USART2_SR_RXNE) { // Received data
buffer[*pRx_counter] = USART2x->DR;
// Reading USART_DR automatically clears the RXNE flag
(*pRx_counter)++;
if((*pRx_counter) >= BufferSize )
(*pRx_counter) = 0;
}
}
*/

void USART2_IRQHandler(void) {
	 receive(USART2, USART2_Buffer_Rx, &Rx2_Counter); 
}


void receive(USART_TypeDef *USARTx, uint8_t *buffer,volatile uint32_t *pCounter) { 
	if(USARTx->ISR & USART_ISR_RXNE) // Check RXNE event
	{  
		buffer[*pCounter] = USARTx->RDR; // Reading RDR clears the RXNE flag 
		(*pCounter)++; 									// Dereference and update memory value 
		if((*pCounter) >= BufferSize)   // Check buffer overflow 
		{ 
			( *pCounter) = 0;             // Circular buffer
		} 
	} 
}