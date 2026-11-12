#include "TIMs.h"

void TIM4_Init(void){ 
	RCC-> APB1ENR1 |= RCC_APB1ENR1_TIM4EN; // Enable clock of Timer 4 
	TIM4->CR1 &= ~TIM_CR1_CMS;         // Clear edge-aligned mode bits 
	TIM4->CR1 &= ~TIM_CR1_DIR;        // Counting direction: Up counting 
	
	
	// Master mode selection 
	// 000: UG bit from the EGR register is used as trigger output (TRGO). 
	// 001: Enable - the Counter Enable signal is used as trigger output (TRGO). 
	// 010: Update - The update event is selected as trigger output (TRGO). 
	// 011: Compare Pulse - The trigger output sends a positive pulse when the 
	// 
	//    CClIF flag is to be set (even if it was already high). 
	// 100: Compare - OClREF signal is used as trigger output (TRGO) 
	// 101: Compare - OC2REF signal is used as trigger output (TRGO) 
	// 110: Compare - OC3REF signal is used as trigger output (TRGO) 
	// 111: Compare - OC4REF signal is used as trigger output (TRGO)
	
	TIM4->CR2 &= ~TIM_CR2_MMS; // Clear master mode selection bits 
	TIM4->CR2 |= TIM_CR2_MMS_2; // Select 100 = OClREF as TRGO 
	// OClM: Output Compare 1 mode 
	TIM4->CCMR1 &= ~TIM_CCMR1_OC1M;	
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; 
	// Clear mode bits 
	// 0110 = PWM mode 1 
	// Timer driving frequency = 80 MHzl(l + PSC) = 80 MHzl(1+7) = 10MHz 
	// Trigger frequency = 10MHz I (1 + ARR) = 10MHzl1000 = 10KHz 
	TIM4-> PSC =  7;       //max 65535
	TIM4->ARR = 999;      //max 65535
	TIM4->CCR1 = 500;      // Duty ration 50%
	
	TIM4->CCER |= TIM_CCER_CC1E; // OCl signal is output 
	TIM4->CR1 |= TIM_CR1_CEN; 
}


