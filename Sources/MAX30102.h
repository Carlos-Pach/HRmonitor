/*
 * MAX30102.h
 *
 *  Created on: Jul 24, 2020
 *      Author: CarlosPach
 */

#ifndef SOURCES_MAX30102_H_
#define SOURCES_MAX30102_H_

#include "Cpu.h"

typedef enum {
	false ,		// 0
	true		// 1
} Bool ;


#define I2C_WRITE_ADDR	0xAE
#define I2C_READ_ADDR	0xAF
#define I2C_ADDR_7BITS  0x57		// 7 bit I2C address

//register addresses
#define REG_INTR_STATUS_1 0x00
#define REG_INTR_STATUS_2 0x01
#define REG_INTR_ENABLE_1 0x02
#define REG_INTR_ENABLE_2 0x03
#define REG_FIFO_WR_PTR 0x04
#define REG_OVF_COUNTER 0x05
#define REG_FIFO_RD_PTR 0x06
#define REG_FIFO_DATA 0x07
#define REG_FIFO_CONFIG 0x08
#define REG_MODE_CONFIG 0x09
#define REG_SPO2_CONFIG 0x0A
#define REG_LED1_PA 0x0C
#define REG_LED2_PA 0x0D
#define REG_PILOT_PA 0x10
#define REG_MULTI_LED_CTRL1 0x11
#define REG_MULTI_LED_CTRL2 0x12
#define REG_TEMP_INTR 0x1F
#define REG_TEMP_FRAC 0x20
#define REG_TEMP_CONFIG 0x21
#define REG_PROX_INT_THRESH 0x30
#define REG_REV_ID 0xFE
#define REG_PART_ID 0xFF

Bool maxim_max30102_init() ;
Bool maxim_max30102_reset(void) ;
Bool maxim_max30102_write_reg(uint8_t uch_addr, uint8_t uch_data) ;
Bool maxim_max30102_read_reg(uint8_t uch_addr, uint8_t *puch_data) ;
Bool maxim_max30102_read_fifo(uint32_t *pun_red_led, uint32_t *pun_ir_led) ;

/* look up table for current to hex values (see MAXIM30102 pg 20) */
static unsigned char currentHex[] = {
		0x0,   // 0 mA
		0x1,   // 0.2 mA
		0x2,   // 0.4 mA
		0x3,   // 0.6 mA
		0x4,   // 0.8 mA
		0x5,   // 1 mA
		0x6,   // 1.2 mA
		0x7,   // 1.4 mA
		0x8,   // 1.6 mA
		0x9,   // 1.8 mA
		0xA,   // 2 mA
		0xB,   // 2.2 mA
		0xC,   // 2.4 mA
		0xD,   // 2.6 mA
		0xE,   // 2.8 mA
		0xF,   // 3 mA
		0x10,   // 3.2 mA
		0x11,   // 3.4 mA
		0x12,   // 3.6 mA
		0x13,   // 3.8 mA
		0x14,   // 4 mA
		0x15,   // 4.2 mA
		0x16,   // 4.4 mA
		0x17,   // 4.6 mA
		0x18,   // 4.8 mA
		0x19,   // 5 mA
		0x1A,   // 5.2 mA
		0x1B,   // 5.4 mA
		0x1C,   // 5.6 mA
		0x1D,   // 5.8 mA
		0x1E,   // 6 mA
		0x1F,   // 6.2 mA
		0x20,   // 6.4 mA
		0x21,   // 6.6 mA
		0x22,   // 6.8 mA
		0x23,   // 7 mA
		0x24,   // 7.2 mA
		0x25,   // 7.4 mA
		0x26,   // 7.6 mA
		0x27,   // 7.8 mA
		0x28,   // 8 mA
		0x29,   // 8.2 mA
		0x2A,   // 8.4 mA
		0x2B,   // 8.6 mA
		0x2C,   // 8.8 mA
		0x2D,   // 9 mA
		0x2E,   // 9.2 mA
		0x2F,   // 9.4 mA
		0x30,   // 9.6 mA
		0x31,   // 9.8 mA
		0x32,   // 10 mA
		0x33,   // 10.2 mA
		0x34,   // 10.4 mA
		0x35,   // 10.6 mA
		0x36,   // 10.8 mA
		0x37,   // 11 mA
		0x38,   // 11.2 mA
		0x39,   // 11.4 mA
		0x3A,   // 11.6 mA
		0x3B,   // 11.8 mA
		0x3C,   // 12 mA
		0x3D,   // 12.2 mA
		0x3E,   // 12.4 mA
		0x3F,   // 12.6 mA
		0x40,   // 12.8 mA (max value before MAX30102 turns off)
} ;

// create user defined functions
void initLED(void) ;
void lightUpLED(void) ;
void sleepMode(uint8_t maxim_addr, uint8_t maxim_data) ;
// create ISR function
void readIRQ(void) ;
void maxim_max30102_mode_change(uint8_t maxim_addr, uint8_t maxim_data) ;
void maxim_sleep() ;	/* finish sleep code later */

/* sleep command for MAX30102 */
#define SLEEP_CMMD	0x80

#endif
