
#include "clock.h"

void setUpClock(unsigned char clock){
	
	switch (clock){
		case 'A':
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
			break;
		case 'B':
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
			break;
		case 'C':
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
			break;
		case 'a':
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
			break;
		case 'b':
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
			break;
		case 'c':
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
			break;
		
		
	}
}


void setPin(GPIO_TypeDef * port, uint32_t pin, uint32_t value)
{
	uint32_t temp = port->ODR;
	uint32_t mask = 1<< pin;
	if(value)
	{
		// if we're setting pin to high
		temp |= mask;
	}
	else
	{
		// if we're setting pin to low
		temp &= ~mask;
	}
	
	port -> ODR =temp;
}



 
uint32_t getPin(GPIO_TypeDef * port, uint32_t pin)
{
	uint32_t temp = port -> IDR;
	temp = temp >> pin;					//Shift the value over by the value of that pin
	temp &= 0x00000001;						//mask to only read that pin
	return temp;									//return the value of that pin
	
}

void setModer(GPIO_TypeDef * port, uint32_t pin, unsigned char mode)
{
	uint32_t temp = port->MODER;
	uint32_t mask;
	
	if (pin < 16){
	
		switch(mode)
		{
			case 'i': //input
			case 'I':
				mask = 0b00 << (pin*2);	
			break;
			case 'o': //output
			case 'O':
				mask = 0b01 << (pin*2);
			break;
			case 'a': //analog
			case 'A':
					mask = 0b11 << (pin*2);
			break;
			case 'f': // alternate function mode
			case 'F':
					mask = 0b10 << (pin*2);
			break;
			default:
						return;
			break;
		}
		temp &= ~(0b11u <<(pin *2));//clears the port
		temp |= mask;			//sets the port
		
		
		port -> MODER = temp;
	}
}
void setPupdr(GPIO_TypeDef * port, uint32_t pin, unsigned char mode)
{
	uint32_t temp = port->PUPDR;
	uint32_t mask;
	
	if (pin < 16){
	
		switch(mode)
		{
			case 'n': //neither
			case 'N':
				mask = 0b00u << (pin*2);	
			break;
			case 'u': //pull up
			case 'U':
				mask = 0b01u << (pin*2);
			break;
			case 'd': //pull down
			case 'D':
					mask = 0b10u << (pin*2);
			break;
		  default:
						return;
			break;
		}
		temp &= ~(0b11u <<(pin *2));//clears the port
		temp |= mask;			//sets the port
		
		
		port -> PUPDR = temp;
	}
}

void setOtyper(GPIO_TypeDef * port, uint32_t pin, unsigned char mode)
{
	if (pin <16)
	{
		uint32_t temp = port->OTYPER;
		uint32_t mask = 1<< pin;
		switch(mode)
			{
				case 'p': //pushpull
				case 'P':
					temp &= ~mask;
				break;
				case 'o': //opendrain
				case 'O':
						temp |= mask;
				break;
				default:
							return;
				break;
			}
		
		port -> OTYPER = temp;
	}	
}

