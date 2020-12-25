/*
 * OLED.h
 *
 *  Created on: Dec 24, 2020
 *      Author: CarlosPach
 */

#ifndef SOURCES_OLED_H_
#define SOURCES_OLED_H_

#include "Cpu.h"

#define PAGE		3
#define COLUMN		0

static unsigned char customChars[] = {
	/* begins on 2nd page, 0th column */
	/*
	0x00, 0x30,
	0x48, 0x44,
	0x22, 0x44,
	0x48, 0x30,	// Heart character (<3) - inverted
	*/

	0x0C, 0x12, 0x22, 0x44, 0x22, 0x12, 0x0C, 0x00 	/* Heart character (<3) - right side up */
} ;

typedef enum{
	err_ok,
	ERR_OUT_OF_RANGE,
	ERR_NOT_ROW_NOT_COL ,
	ERR_UNKNOWN
} tOLED_ERR ;

uint8_t printHeart(unsigned char page, unsigned char column) ;	/* prints heart on OLED display */
void initOLED(void) ;

#endif /* SOURCES_OLED_H_ */
