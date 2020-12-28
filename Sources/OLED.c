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
 * 	Parameters:
 * 		[in] page		- page number from 0 to 7 (inclusive)
 * 		[in] column		- column number from 0 to 127 (inclusive)
 *
 * 	Return Value: Error code
 *
 *	///////////////////////////////////////////
*/
uint8_t printHeart(unsigned char page, unsigned char column){
	static unsigned char i, j, ch, n ;
	ch = 0 ;
	n = sizeof(customChars)/sizeof(customChars[0]) ;	/* size of arr */

	/* check if page or column is out of range */
	if((page < PAGE || page > PAGE_MAX) || (column < 0 || column > COLUMN_MAX)){
		return ERR_OUT_OF_RANGE;
	}
	/* no out of range error found */

	/* print data to OLED display */
	if(LCD1_SetRowCol(page, column) != 0x00){
		return ERR_NOT_ROW_NOT_COL;
	}

	for(i = 0; i < n; i++){
		LCD1_WriteData(customChars[ch]) ;
		ch++ ;
	}
	/* return ok */
	return err_ok ;
}

/*
 *	/////////////////////////////////////////
 * 	Function name: initOLED
 *  Purpose: Initializes OLED capabilities
 *  Details: Tests OLED functionality by displaying custom chars
 *  		 and testing correct cursor placement
 *
 * 	Parameters:
 * 		None
 * 	Return Value:
 * 		None
 *  ///////////////////////////////////////////
*/
void initOLED(void){
	/* test all 8 lines of OLED display */
    for(unsigned char i = 0; i < 8; i++){	/* print to all rows on display */
	  LCD1_PrintString(i, 0, "Hello there") ;
    }
	LCD1_Clear() ;

	/* PAGE and COLUMN set as macro on OLED.h */
	if(printHeart(PAGE, COLUMN) != err_ok){
		LCD1_PrintString(0, 0, "Error in printHeart") ;
		return ;
	}
	LCD1_Clear() ;
	if(setUpHeartO2(PAGE, COLUMN) != err_ok){
		LCD1_PrintString(1, 0, "Error in O2") ;
		return ;
	}
	LCD1_Clear() ;
}


/*
 *	/////////////////////////////////////////
 * 	Function name: setUpHeartO2
 *  Purpose: Initializes OLED for O2 and heart display
 *  Details: Sets a static image of a heart and O2 symbol
 *  		 on the OLED display
 *
 * 	Parameters:
 * 		[In] - page
 * 		[In] - column
 * 	Return Value:
 * 		Error code
 *  ///////////////////////////////////////////
 *  */
uint8_t setUpHeartO2(unsigned char page, unsigned char column){
	static unsigned char i, j, ch, n, hyp ;
	ch = 0 ;	/* keeps track of where char is inside array */
	n = sizeof(customChars)/sizeof(customChars[0]) ;	/* array size */

	/* print first custom char to PAGE, then second custom char to PAGE+1 */
	for(i = page; i < (page + 2); i++){
		if(LCD1_SetRowCol(i, column) != 0x00){ return ERR_NOT_ROW_NOT_COL ; }
		for(j = 0; j < 8; j++){		/* using small font, therefore max custom char is 8 columns per page */
			LCD1_WriteData(customChars[ch]) ;
			ch++ ;		/* keep track of ch in between for loops to print correct character */
		}
		/* assign hyp with beginning of hyphen symbol */
		for(hyp = (n - 8); hyp < n; hyp++){	/* print hyphen symbol */
			LCD1_WriteData(customChars[hyp]) ;
		}
	}

	/* return ok */
	return err_ok ;
}

