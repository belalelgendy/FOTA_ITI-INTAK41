/*
 * main.c
 *
 *  Created on: Apr 27, 2021
 *      Author: Amira
 */

#define F_CPU 8000000
#include "STD_Types.h"
#include "avr/delay.h"
#include "avr/boot.h"
#include <avr/eeprom.h>
#include "avr/interrupt.h"
#include "parse.h"

#define  TOGGLE_LED(reg,bit)        (reg=reg^(1<<bit))
#define SET_BIT(reg,bit)            (reg=reg|(1<<bit))

unsigned char App_Code[]=
{ 0x0C, 0x94, 0x2A, 0x00, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00
		, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00
		, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00
		, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00
		, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00, 0x0C, 0x94, 0x34, 0x00
		, 0x0C, 0x94, 0x34, 0x00, 0x11, 0x24, 0x1F, 0xBE, 0xCF, 0xE5, 0xD8, 0xE0, 0xDE, 0xBF, 0xCD, 0xBF
		, 0x0E, 0x94, 0x40, 0x00, 0x0C, 0x94, 0x73, 0x00, 0x0C, 0x94, 0x00, 0x00, 0x83, 0xE3, 0x89, 0xB9
		, 0x59, 0x98, 0x54, 0x9A, 0x53, 0x9A, 0x08, 0x95, 0x57, 0x9A, 0x08, 0x95, 0x57, 0x98, 0x08, 0x95
		, 0x8B, 0x9A, 0x80, 0xE2, 0x90, 0xE0, 0x0E, 0x94, 0x5E, 0x00, 0x81, 0x30, 0x21, 0xF4, 0x80, 0xE2
		, 0x90, 0xE0, 0x60, 0xE0, 0x03, 0xC0, 0x80, 0xE2, 0x90, 0xE0, 0x61, 0xE0, 0x0E, 0x94, 0x66, 0x00
		, 0x48, 0xE0, 0x28, 0xEC, 0x30, 0xE0, 0x82, 0xB3, 0x84, 0x27, 0x82, 0xBB, 0x80, 0xE1, 0x97, 0xE2
		, 0xF9, 0x01, 0x31, 0x97, 0xF1, 0xF7, 0x01, 0x97, 0xD9, 0xF7, 0xF5, 0xCF, 0xE1, 0x99, 0xFE, 0xCF
		, 0x9F, 0xBB, 0x8E, 0xBB, 0xE0, 0x9A, 0x99, 0x27, 0x8D, 0xB3, 0x08, 0x95, 0x26, 0x2F, 0xE1, 0x99
		, 0xFE, 0xCF, 0x9F, 0xBB, 0x8E, 0xBB, 0x2D, 0xBB, 0x0F, 0xB6, 0xF8, 0x94, 0xE2, 0x9A, 0xE1, 0x9A
		, 0x0F, 0xBE, 0x01, 0x96, 0x08, 0x95, 0xF8, 0x94, 0xFF, 0xCF

		, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
		, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//#define CODE_SIZE  256
//#define NO_OF_PAGES  2

unsigned char arr2[CODE_SIZE];

#define NO_OF_PAGES_new  13
//#define FINAL_ARR_SIZE_new  256 //from array tool

int main(void)
{
	UART_Init();

	uint8  i , pageNo ;
	int NO_OF_PAGES=13;
	uint8_t value=10;
	SET_BIT(DDRD,5);
	SET_BIT(DDRD,2);


	uint8_t NoFlash_f=0x00;

	unsigned char our_data_new[FINAL_ARR_SIZE];


	value = eeprom_read_byte ((const uint8_t*)32);

	/*Blink a Led to indicate the BLD SW */
	for(i = 0 ; i < 3 ; i++)
	{
		TOGGLE_LED(PORTD,2);
		_delay_ms(1000);
	}


	if(value==0x01)  // Indicates NewApp is Available
	{
		_delay_ms(1500);
		UART_Send('L');

		_delay_ms(1500);
		for(pageNo = 0 ; pageNo < NO_OF_PAGES_new ; pageNo++)
		{
			UART_Send('M');
			UART_Receive_Str(arr2);
			final_array_of_data(arr2,our_data_new);

			boot_program_page( pageNo, &our_data_new[0]);
		}

		asm("jmp 0");
	}

	else
	{

		for(pageNo = 0 ; pageNo < NO_OF_PAGES ; pageNo++)
		{
			boot_program_page( pageNo, &App_Code[SPM_PAGESIZE*pageNo]);
		}

		asm("jmp 0");
	}

}
