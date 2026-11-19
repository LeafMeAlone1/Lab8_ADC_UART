#ifndef __STM32L476R_NUCLEO_ADC_H
#define __STM32L476R_NUCLEO_ADC_H
#include "stm32l476xx.h"

	extern 	volatile float Result;
	
	void ADC1_Init(void);
	void ADC1_Wakeup(void);
	
	
	void ADC1_2_IRQHandler (void);
	void ADC1_Read(void);
	

#endif