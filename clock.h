#ifndef __STM32L476R_NUCLEO_CLOCK_H
#define __STM32L476R_NUCLEO_CLOCK_H
#include "stm32l476xx.h"
#include "clock.h"

void setUpClock(unsigned char);

void setPin(GPIO_TypeDef * port, uint32_t pin, uint32_t value);

uint32_t getPin(GPIO_TypeDef * port, uint32_t pin);
void setModer(GPIO_TypeDef * port, uint32_t pin, unsigned char mode);
void setPupdr(GPIO_TypeDef * port, uint32_t pin, unsigned char mode);
void setOtyper(GPIO_TypeDef * port, uint32_t pin, unsigned char mode);

#endif



