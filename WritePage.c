/*
 * WritePage.c
 *
 *  Created on: Apr 27, 2021
 *      Author: Amira
 */
#include "WritePage.h"
#include "avr/interrupt.h"
#include "avr/boot.h"
#include "avr/delay.h"

	void boot_program_page (uint16 page, uint8 *buf)
	{
		uint16 i;
		uint8 sreg;
		uint32 address;
		uint16 word ;

		// Disable interrupts.
		sreg = SREG;
		cli();
		address =page * SPM_PAGESIZE ;
		//LCD_GotoXY(0,0);
		//LCD_WriteNumber(address);
		_delay_ms(100);

		boot_page_erase_safe (address);

		for (i=0; i<SPM_PAGESIZE; i+=2)
		{
			// Set up little Endian word.
			word  = *buf++;
			word += (*buf++) << 8;

			boot_page_fill_safe(address + i, word);
		}

		boot_page_write_safe (address);     // Store buffer in flash page.

		// Reenable RWW-section again. We need this if we want to jump back
		// to the application after bootloading.

		boot_rww_enable_safe();

		// Re-enable interrupts (if they were ever enabled).

		SREG = sreg;
	}
