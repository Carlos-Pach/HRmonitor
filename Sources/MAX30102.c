/*
 * MAX30102.c
 *
 *  Created on: Jul 24, 2020
 *      Author: CarlosPach
 */

#include "Cpu.h"
#include "MAX30102.h"

/*
 *  ========================================================
 *  Function name: maxim_max30102_init
 *
 *  Purpose: Initialize the MAX30102
 *  Details: This function initializes the MAX30102
 *
 *  Parameters:
 *  	None
 *
 *  Return Value:
 *  	true on success
 *  ========================================================
 */
Bool maxim_max30102_init(){
	if(!maxim_max30102_write_reg(REG_INTR_ENABLE_1, 0xC0)){	// INTR setting
		return false ;
	}
	if(!maxim_max30102_write_reg(REG_INTR_ENABLE_2, 0x00)){
		return false ;
	}
	if(!maxim_max30102_write_reg(REG_FIFO_WR_PTR, 0x00))  //FIFO_WR_PTR[4:0]
	    return false;
    if(!maxim_max30102_write_reg(REG_OVF_COUNTER, 0x00)){  //OVF_COUNTER[4:0]
    	return false;
    }
    if(!maxim_max30102_write_reg(REG_FIFO_RD_PTR, 0x00)){  //FIFO_RD_PTR[4:0]
    	return false;
    }
    if(!maxim_max30102_write_reg(REG_FIFO_CONFIG, 0x0F)){  //sample avg = 1, fifo rollover=false, fifo almost full = 17
    	return false;
    }
    // 0x02 --> 0x07 --> 0x02 --> 0x07
    if(!maxim_max30102_write_reg(REG_MODE_CONFIG, 0x02)){  //0x02 for Red only, 0x03 for SpO2 mode 0x07 multimode LED
    	return false;
    }
    // 0x27 --> 0x2B (ADC: 4096 [nA], SPO2: 200 [samples/s], LED pulse width: [400 us]) --> 0x27
    if(!maxim_max30102_write_reg(REG_SPO2_CONFIG, 0x27)){  // SPO2_ADC range = 4096nA, SPO2 sample rate (100 Hz), LED pulseWidth (400uS)
    	return false;
    }

    // 0x24 --> 0x2C --> 0x24 --> 0x3F (~12.6 mA) --> 0x24
    // 0x24 --> 0x1F	(~6.2 [mA])
    if(!maxim_max30102_write_reg(REG_LED1_PA, currentHex[0x24])){   //Choose value for ~ 7mA for LED1
    	return false;
    }
    // 0x24 --> 0x2C --> 0x24 --> 0x1F (~ 6.2 [mA])
    if(!maxim_max30102_write_reg(REG_LED2_PA, 0x24)){   // Choose value for ~ 7mA for LED2
	  	return false;
    }
    /* this function does not work because MAX30102 lacks Pilot LED */
    if(!maxim_max30102_write_reg(REG_PILOT_PA, 0x7F)){   // Choose value for ~ 25mA for Pilot LED
    	return false;
    }
	return true ;
}

/*
 *  ========================================================
 *  Function Name: maxim_max30102_write_reg
 *
 *  Purpose: Write a value to a MAX30102 register
 *  Details: This function writes a value to a MAX30102 register
 *
 *  Parameters:
 *  	NAME				DESCRIPTION
 *  	[In] uch_addr	- register address
 *  	[In] puch_data	- register data
 *
 *  Return Value:
 *  	true on success
 *  ========================================================
 */
Bool maxim_max30102_write_reg(uint8_t uch_addr, uint8_t uch_data) {
	char ach_i2c_data[2] ;
	ach_i2c_data[0] = uch_addr ;
	ach_i2c_data[1] = uch_data ;

	// 3rd and 5th arguments are number of bytes being written
	if(GI2C1_WriteAddress(I2C_ADDR_7BITS, &ach_i2c_data[0], 1, &ach_i2c_data[1], 1) == 0x00){
		return true ;
	}
	return false ;
}

/*
 *  ========================================================
 *  Function Name: maxim_max30102_reset
 *
 *  Purpose: Reset the MAX30102
 *  Details: This function resets the MAX30102
 *
 *  Parameters:
 *		None
 *
 *  Return Value:
 *  	true on success
 *  ========================================================
 */
Bool maxim_max30102_reset(void){
	if(!maxim_max30102_write_reg(REG_MODE_CONFIG, 0x40)){
		return false ;
	}
	else{
		return true ;
	}
}

/*
 *  ========================================================
 *  Function Name: maxim_max30102_read_reg
 *
 *  Purpose: Reads a MAX30102 register
 *  Details: This function reads a MAX30102 register
 *
 *  Parameters:
 *		NAME				DESCRIPTION
 *		[In] uch_addr	- register address
 *		[Out] puch_data	- register data
 *
 *  Return Value:
 *  	true on success
 *  ========================================================
 */
Bool maxim_max30102_read_reg(uint8_t uch_addr, uint8_t *puch_data){
	char ch_i2c_data ;
	uint8_t *var ;				// change: var --> *var
	ch_i2c_data = uch_addr ;
	var = puch_data ;

	// changing from &var --> &ch_i2c_data
	if(GI2C1_WriteAddress(I2C_ADDR_7BITS, &ch_i2c_data , 1, &ch_i2c_data , 1) != 0x00){
		return false ;
	}
	// return value for function should be RES_OK (0x00) if address is read correctly
	if(GI2C1_ReadAddress(I2C_ADDR_7BITS, &ch_i2c_data, 1, &ch_i2c_data, 1) == 0x00){ // &var --> &ch_i2c_data
		*puch_data = (uint8_t)ch_i2c_data ;
		return true ;
	}
	else{
		return false ;
	}
}

/*
 *  ========================================================
 *  Function Name: maxim_max30102_mode_change
 *
 *  Purpose: Changes modes based on user input from switch
 *  Details: This function changes LED modes (red or multiLED)
 *
 *  Parameters:
 *		NAME					DESCRIPTION
 *		[In] maxim_addr		- register address
 *		[In] maxim_data		- register data
 *
 *  Return Value:
 *  	none
 *  ========================================================
 */
void maxim_max30102_mode_change(uint8_t maxim_addr, uint8_t maxim_data){
	// write to maxim_max30102_write_reg
	maxim_max30102_write_reg(maxim_addr, maxim_data) ;
}

/*
 * ==========================================================
 * Function name: sleepMode
 * Purpose: Switches MAX30102 to sleep/wake-up
 * Details: This function either puts the MAX30102 to sleep or
 * 			wakes up the MAX30102
 *
 * Parameters:
 * 		NAME					DESCRIPTION
 * 		[In] maxim_addr		- register address
 * 		[In] maxim_data		- register data
 *
 * 	Return value:
 * 		none
 * 	==========================================================
*/
void sleepMode(uint8_t maxim_addr, uint8_t maxim_data){
	/* write to maxim_max30102_write_reg */
	maxim_max30102_write_reg(maxim_addr, maxim_data) ;
}
/*
 *  ========================================================
 *  Function Name: maxim_max30102_read_fifo
 *
 *  Purpose: Reads a set of samples from the MAX30102 FIFO register
 *  Details: This function reads a set of samples from the MAX30102 register
 *
 *  Parameters:
 *		NAME					DESCRIPTION
 *		[Out] *pun_red_led		- register address
 *		[Out] *pun_ir_led		- register data
 *
 *  Return Value:
 *  	true on success
 *  ========================================================
 */
Bool maxim_max30102_read_fifo(uint32_t *pun_red_led, uint32_t *pun_ir_led){
	uint32_t un_temp ;			// used as a dummy variable to get data from ach_i2c_data array
	unsigned char uch_temp ;	// used as a dummy variables to get data from MAX30102
	*pun_red_led = 0 ;			// ptr used for aun_red_buffer[i]
	*pun_ir_led = 0 ;			// ptr used for aun_ir_buffer[i]
	char ach_i2c_data[6] ;		// char array for holding {I2C_7BIT_ADDR, data ...}

	// read and clear status register
	maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_temp) ;			// MEM_I2C[0x00] --> ADDR[uch_temp]
	maxim_max30102_read_reg(REG_INTR_STATUS_2, &uch_temp) ;			// MEM_I2C[0x01] --> ADDR[uch_temp]

	// fill up i2c array
	ach_i2c_data[0] = REG_FIFO_DATA ;	// ach_i2c_data = {0x07, prevData, ...}

	// write and read from max30102
	// &ach_i2c_data[1] --> &ach_i2c_data[0]
	if(GI2C1_WriteAddress(I2C_ADDR_7BITS, &ach_i2c_data, 1, &ach_i2c_data[0], 1) != 0x00){	// change: &ach_i2c_data[0] --> &ach_i2c_data[1]
		return false ;
	}
	// 3rd and 5th arguments changed to 1 and 5 respectively, 4th argument changed to &data[1]
	// &ach_i2c_data[0] reads from max30102 and &ach_i2c_data[1] begins reading (5) bytes
	if(GI2C1_ReadAddress(I2C_ADDR_7BITS, &ach_i2c_data, 1, &ach_i2c_data[0], 6) != 0x00){	// &ach_i2c_data[1], 5 --> &ach_i2c_data[0], 6
		return false ;
	}

	// add up values for red LED
	un_temp = (unsigned char)ach_i2c_data[0] ;
	un_temp = (un_temp << 16) ;
	*pun_red_led += un_temp ;
	un_temp = (unsigned char)ach_i2c_data[1] ;
	un_temp = (un_temp << 8) ;
	*pun_red_led += un_temp ;
	un_temp = (unsigned char)ach_i2c_data[2] ;
	*pun_red_led += un_temp ;

	// add up values for ir LED
	un_temp = (unsigned char)ach_i2c_data[3] ;
	un_temp <<= 16 ;
	*pun_ir_led += un_temp ;
	un_temp = (unsigned char)ach_i2c_data[4] ;
	un_temp <<= 8 ;
	*pun_ir_led += un_temp ;
	un_temp = (unsigned char)ach_i2c_data[5] ;
	*pun_ir_led += un_temp ;
	*pun_red_led &= 0x03FFFF ;  //Mask MSB [23:18]
	*pun_ir_led &= 0x03FFFF ;  //Mask MSB [23:18]

	return true ;
}
