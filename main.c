#include "stm32l476xx.h"
#include "ADC.h"
#include "USART.h"
#include "clock.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void equation(volatile float measurement, char *str, size_t len);


int main(void){
	
	ADC1_Init();
	USART_Init(USART2);
	
	  uint8_t input = 0;
		char temperature [15];  // form "temp = xx.xxx"
	
	
	while(1) 
	{ 

		
		USART_Read (USART2, &input, 1);
		USART_Write(USART2, &input, 1);
		if (input == 't'  || input == 'T')
		{	
			ADC1_Read();
			equation(Result, temperature, sizeof(temperature));
			USART_Write(USART2,(uint8_t*) temperature, strlen(temperature));                  // send temperature
		}
	} 
		
	 /*while(1)       // 2) RX test: echo
    {                                      
         uint8_t c;
         USART_Read (USART2, &c, 1);
         USART_Write(USART2, &c, 1);                  // send it back

    } 
	        */
	 /*
	while(1)       
	{                                      
    USART_Read(USART2, &input, 1);
    
    // Echo to prove PuTTY is still connected
    USART_Write(USART2, &input, 1); 

    if (input == 't'  || input == 'T')
    {		
        USART_Write(USART2, (uint8_t*)"\r\n[1] Got T, starting ADC...\r\n", 30);
        
        ADC1_Read();
        
        USART_Write(USART2, (uint8_t*)"[2] ADC finished, doing math...\r\n", 33);
        
        equation(Result, temperature, sizeof(temperature));
        
        USART_Write(USART2, (uint8_t*)"[3] Math finished, sending temp...\r\n", 36);
        
        USART_Write(USART2, (uint8_t*) temperature, strlen(temperature));                  
    }
	}*/
}     

  void equation(volatile float measurement, char *str, size_t len)
 {
	
	float cal1 = (float)(*(uint16_t*) 0x1FFF75A8);
	float cal2 = (float)(*(uint16_t*)0x1FFF75CA);

	 measurement *= 1.1; // scaling (3.3/3) =1.1
	 
	float temp = ((80.0)*(measurement-cal1));
	temp = (temp/(cal2-cal1));
	temp = (temp+30.0);
	 
	// char str[20]; //helps conver numbers to string
	//display min
	snprintf(str, len, "%.4f\r\n", temp); // Convert integer to string
	
 }