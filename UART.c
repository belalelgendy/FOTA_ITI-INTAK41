
#include "UART.h"


static void(*UART_RX_Fptr)(void)=NULLPTR;
static void(*UART_TX_Fptr)(void)=NULLPTR;
void UART_Init(void)
{
	// baud rate 9600
	UBRRL=103;
	//normal speed
	SET_BIT(UCSRA,U2X);
	
	//DEFAULT FRAME  8data 1 stop no parity
	//ENABLE
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
}



void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB,RXCIE);
}
u8 UART_Receive(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}
void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
}/*
void UART_ReceiveString(u8*str)
{
	u8 i=0;
	str[i]=UART_Receive();
	for (i=0;str[i]!='#';)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]='\0';
}*/





