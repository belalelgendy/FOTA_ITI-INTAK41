

#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_


#include "UART.h"

#define END_CHAR   13

void UART_SendStr(u8* str);
void UART_RxStr(u8* str);
void UART_SendNum32U(u32 num);
u32 UART_RecNum32U(void);



#endif /* UART_SERVICES_H_ */