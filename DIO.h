/*
 * DIO.h
 *
 *  Created on: Dec 12, 2020
 *      Author: Al Badr
 */

#ifndef DIO_H_
#define DIO_H_

#include "STD_Types.h"
#include "DIO_config.h"

void DIO_Init(void);

void DIO_WriteChannel(DIO_enuChannel Channel_ID , uint8 value);
void DIO_WritePort(DIO_enuPort Port_ID , uint8 value);

uint8 DIO_ReadChannel(DIO_enuChannel PinChannel);
uint8 DIO_ReadPort( DIO_enuPort PortID);

#endif /* DIO_H_ */
