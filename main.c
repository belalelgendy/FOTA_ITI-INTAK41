#include "DIO_interface.h"
#include "LCD.h"
#include "KeyPad.h"
#include "stepper.h"
#include "Sensors.h"
#include "Timer_Services.h"
#include "UART.h"



int main(void)
{	sei();
	DIO_Init();
	LCD_Init();
    UART_Init();
	u8 x=0;
	
u8 c=0;    
	while(1)
	{
	
	  x=UART_Receive();

	  LCD_WriteChar(x);
	 
	
	 
	  
	}
			
}


//void __vector_1(void)__attribute__((signal));
 //tell the comp that the fun from asignal
 //push the reg values in stack and status reg also not like the original fun call 
	

	
	
	
	
