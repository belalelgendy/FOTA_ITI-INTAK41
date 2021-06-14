#include "UART_Services.h"


void UART_SendStr(u8* str)
{
	for (u8 i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
}

void UART_RxStr(u8* str)
{
	u8 i;
		str[i]=UART_Receive();
		for (i=0;str[i]!=END_CHAR;)
		{
			i++;
			str[i]=UART_Receive();
		}
		str[i]='\0'; //or =0
		
}

void UART_SendNum32U(u32 num)
{/*
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));*/
u8* p=&num;
UART_Send(p[0]);
UART_Send(p[1]);
UART_Send(p[2]);
UART_Send(p[3]);
}
u32 UART_RecNum32U(void)
{/*
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	u8 b4=UART_Receive();
	u32 num=0;
	num=b1 | (u32)b2<<8 |  (u32)b3<<16 |  (u32)b4<<24;
*/
	u32 num;
	u8*p=&num;
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	return num;
}


