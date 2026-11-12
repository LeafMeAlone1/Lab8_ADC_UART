#include "ADC.h"


void ADC1_Init (void) { 
	int wait_time; 
	// To start ADC operations, the following sequence should be applied 
	// DEEPPWD = e: ADC not in deep-power down 
	// DEEPPWD = 1: ADC in deep-power-down (default reset state) 
	if ((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD) { 
		// Exit deep power down mode if still in that state 
		ADC1->CR &= ~ADC_CR_DEEPPWD; 
	} 
	// Enable the ADC internal voltage regulator 
	// Before performing any operation such as Launching a calibration or 
	// enabling the ADC, the ADC voltage regulator must first be enabled and 
	// the software must wait for the regulator start-up time. 
	ADC1->CR |= ADC_CR_ADVREGEN; 
	// Wait for ADC voltage requlator start-up time. The software must wait for
		// the startup time of the ADC voltage regulator (T_ADCVREG_STUP, i.e., 20 
	// us) before Launching a calibration or enabling the ADC. 
	wait_time = 20 * (80000000 / 1000000); 
	while (wait_time != 0) { 
		wait_time--; 
	}

	
void ADC1_2_IRQHandler (void)
{
		if ((ADC1->ISR & ADC_ISR_EOC) == ADC_ISR_EOC) 
		{ 
			// For a regular channeL, check End of Conversion (EOC) fLag 
			// Reading ADC data register (DR) cLears the EOC fLag 
			Result = ADC1->DR; 
			} 
		else if ((ADC1->ISR & ADC_ISR_JEOS) == ADC_ISR_JEOS)
		{ 
			// For injected channels, check End of Sequence (JEOS) fLag 
			// Reading injected data registers does not clear the JEOS flag 
			// Each injected channel has 
			Result_l 
			ADC1->JDR1; 
			Result_2 = ADC1->JDR2; 
			Result_3 
			ADC1->JDR3; 
			Result_4 
			a dedicated data register 
			// Injected channel 1 
			// Injected channel 2 
			// Injected channel 3 
			// Injected channeL 4 
			ADC1->JDR4; 
			ADC1->ISR I= ADC_ISR_EOS; // CLear the flab by writing 1 to it 
		}
}
