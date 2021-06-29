

#ifndef UART_H_
#define UART_H_

#include "MemMap.h"
#include "StdType.h"
#include "Utils.h"

#define NULLPTR  0
#define  END_BIT '#'



void UART_Init(void);


void UART_Send(u8 data);
void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);


#endif /* UART_H_ */
