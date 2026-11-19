#include "ADC.h"

volatile float Result;
void ADC1_Init()
{
		RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
	
    ADC1->CR &= ~ADC_CR_ADEN;
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_BOOSTEN;
    ADC123_COMMON->CCR |= ADC_CCR_VREFEN;
    ADC123_COMMON->CCR &= ~ADC_CCR_PRESC;
    ADC123_COMMON->CCR |= ADC_CCR_CKMODE_0;
    ADC123_COMMON->CCR &= ~(ADC_CCR_DUAL);
    ADC1_Wakeup();
    ADC1->CFGR &= ~ADC_CFGR_RES;
    ADC1->CFGR &= ~ADC_CFGR_ALIGN;
    ADC1->SQR1 &= ~ADC_SQR1_L;
    ADC1->SQR1 |= 0x00000440;
    ADC1->SMPR2 |= ADC_SMPR2_SMP17;
    ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_17;
    //ADC1->SMPR1 |= ADC_SMPR1_SMP0;
    ADC1->CFGR &= ~ADC_CFGR_CONT;
    ADC1->CFGR &= ~ADC_CFGR_EXTEN;
	
		ADC1->CR |= ADC_CR_ADCAL;
		while ((ADC1->CR & ADC_CR_ADCAL) == ADC_CR_ADCAL);
	
		ADC123_COMMON->CCR |= ADC_CCR_TSEN;
    ADC1->CR |= ADC_CR_ADEN;
    while ((ADC1->ISR & ADC_ISR_ADRDY) == 0);
}
	
void ADC1_Wakeup(void) 
{ 
	volatile int wait_time; 
	// To start ADC operations, the following sequence should be applied 
	// DEEPPWD = e: ADC not in deep-power down 
	// DEEPPWD = 1: ADC in deep-power-down (default reset state) 
	if ((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD)
	{ 
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
	while (wait_time != 0)
	{ 
		wait_time--; 
	} 
}

/*void ADC1_2_IRQHandler (void)
{ 
	if ((ADC1->ISR & ADC_ISR_EOC) == ADC_ISR_EOC)
	{ 
		// For a regular channeL, check End of Conversion (EOC) fLag 
		// Reading ADC data register (DR) cLears the EOC fLag 
		Result = ADC1->DR; 
	} 
	// clear handler flag;
	
}      */

	void ADC1_Read(void)
{
		ADC1->ISR |= ADC_ISR_EOC;
    ADC1->CR |= ADC_CR_ADSTART;
    while ((ADC1->ISR & ADC_ISR_EOC) == 0);
    Result = (float)ADC1->DR;                    // reading DR clears EOC
}

	