/*
 * OLED.h
 *
 *  Created on: Dec 24, 2020
 *      Author: CarlosPach
 */

#ifndef SOURCES_OLED_H_
#define SOURCES_OLED_H_

#include "Cpu.h"

#define PAGE		2
#define PAGE_MAX	7
#define COLUMN		0
#define COLUMN_MAX 	127

static unsigned char customChars[] = {
	/* begins on 2nd page, 0th column */

	/* small fonts */
	0x0C, 0x12, 0x22, 0x44, 0x22, 0x12, 0x0C, 0x00, 	/* Heart character <3 - right side up (8x8) */
	0x3C, 0x42, 0x42, 0x42, 0x3C, 0x90, 0xD0, 0xA0,		/* O2 symbol (8x8) */
	0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00 		/* hyphen symbol (8x8) (ASCII: 0x2D) */

} ;

typedef enum{
	err_ok,
	ERR_OUT_OF_RANGE,
	ERR_NOT_ROW_NOT_COL ,
	ERR_UNKNOWN
} tOLED_ERR ;

uint8_t printHeart(unsigned char page, unsigned char column) ;	/* prints heart on OLED display */
void initOLED(void) ;
uint8_t setUpHeartO2(unsigned char page, unsigned char column) ; /* prints heart and O2 symbol on OLED display */

#endif /* SOURCES_OLED_H_ */
