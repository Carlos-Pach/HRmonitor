/*
 * HC06.c
 *
 *  Created on: Dec 26, 2020
 *      Author: CarlosPach
 */

#include "Cpu.h"
#include "HC06.h"

/*
 *	///////////////////////////////////////////////
 *	Function name: printStringHC06
 *	Purpose: Sends string to BT module
 *	Details: Sends messages to BT module's connected terminal
 *			 Assume newline not first char in msg. Newline supported.
 *
 * 	Parameters:
 * 		[In] *msgPtr		- Message (as a string) to send
 *
 * 	Return values:
 * 		Error codes
 * 	////////////////////////////////////////////////
*/
uint8_t printStringHC06(unsigned char *msgPtr){
	/* check if a message was received */
	if(*msgPtr == '\n' || *msgPtr == '\0'){
		return BT_ERR_NO_MSG ;
	}
	/* print msg to BT terminal */
	while(*msgPtr != '\0'){
		if(*msgPtr == '\n'){
			BT1_SendChar('\n') ;
			return BT_NO_ERR ;
		} else{
			BT1_SendChar(*msgPtr) ;
			*msgPtr++ ;
		}
	}
	return BT_NO_ERR ;
}

