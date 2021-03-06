/*
 * HC06.h
 *
 *  Created on: Dec 26, 2020
 *      Author: CarlosPach
 */

#ifndef SOURCES_HC06_H_
#define SOURCES_HC06_H_

#define TEST_BT_VAL		120
#define ASCII_MASK		48

#include "Cpu.h"
#include "BT1.h"

unsigned char arrConvFlag = 0 ;	/* flip to 1 when first number is converted */
uint8_t heartRateArr[4] = {'\n'} ;

typedef enum{	/* error codes for HC-06 */
	BT_NO_ERR = 0,
	BT_ERR_STR,
	BT_ERR_NO_MSG,
	BT_ERR_INVALID_NUM,
	BT_ERR_OOR
} BT_ERR;

uint8_t printStringHC06(unsigned char *msgPtr) ;
uint8_t convertToStrHC06(int32_t val) ;	/* may use instead of sprintf() */

#endif /* SOURCES_HC06_H_ */
