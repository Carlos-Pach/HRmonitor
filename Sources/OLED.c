/*
 * OLED.c
 *
 *  Created on: Dec 24, 2020
 *      Author: CarlosPach
 */

#include "Cpu.h"
#include "OLED.h"

/*
 *	////////////////////////////////////////////
 *	Function name: printHeart
 * 	Purpose: Prints a static image of a heart on the OLED display
 * 	Description: Prints a custom character on the OLED display.
 * 				 Page starts off at (2) and ends at (7). Column
 * 				 starts off at (0) and ends at (127).
 *
 * 	Parameters:	 page, column
 *
 * 	Return Value: ERROR CODES
 *
 *	///////////////////////////////////////////
*/
uint8_t printHeart(unsigned char page, unsigned char column){
	static unsigned char i, j, ch ;
	ch = 0 ;

	/* check if page or column is out of range */
	if((page < 2 || page > 7) || (column < 0 || column > 127)){
		return ERR_OUT_OF_RANGE;
	}
	/* no out of range error found */

	/* print data to OLED display */
	if(LCD1_SetRowCol(page, column) != 0x00){
		return ERR_NOT_ROW_NOT_COL;
	}

	for(i = 0; i < sizeof(customChars)/sizeof(customChars[0]); i++){
		LCD1_WriteData(customChars[i]) ;
	}

	/* return ok */
	return err_ok ;
}

void initOLED(void){
	LCD1_Clear() ;
	LCD1_PrintString(0, 0, "Hello there") ;
	LCD1_Clear() ;

	/* PAGE and COLUMN set as macro on OLED.h */
	printHeart(PAGE, COLUMN) ;
}
