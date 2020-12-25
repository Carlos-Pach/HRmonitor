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

// create user defined functions
void initLED(void) ;
void lightUpLED(void) ;
void sleepMode(uint8_t maxim_addr, uint8_t maxim_data) ;
// create ISR function
void readIRQ(void) ;
void maxim_max30102_mode_change(uint8_t maxim_addr, uint8_t maxim_data) ;

/* sleep command for MAX30102 */
#define SLEEP_CMMD	0x80

#endif
