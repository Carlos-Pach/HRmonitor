/* ###################################################################
**     Filename    : main.c
**     Project     : HRmonitor
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-07-24, 16:08, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "GI2C1.h"
#include "MCUC1.h"
#include "WAIT1.h"
#include "CI2C1.h"
#include "CsIO1.h"
#include "IO1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "algorithm.h"
#include "MAX30102.h"

#define MAX_BRIGHTNESS	255

uint32_t aun_ir_buffer[BUFFER_SIZE] ;	// IR LED sensor data
int32_t n_ir_buffer_length ;		// data length
uint32_t aun_red_buffer[BUFFER_SIZE] ;	// red LED sensor data
int32_t n_sp02 ;					// SPO2 value
int8_t ch_spo2_valid ;				// indicator to show if SPO02 calculation is valid
int32_t n_heart_rate ;				// heart rate value
int8_t ch_hr_valid ;				// indicator to show if heart rate calculation is valid
uint8_t uch_dummy ;					// char used to get keyboard input ... might remove

unsigned long delay = 0x10000 ;

void Delay(unsigned long delay){
	while(delay > 0) delay-- ;
}

void initLED(void){
  // set up on-board LED for testing
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Enable Port B Clock Gate Control*/
  //SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK ;
  //PORTD_GPCLR = 0x000101000 ;	// set up PORTD 1 for GPIO
  PORTB_PCR21 = 0x100 ; /*Blue Led, configured as Alternative 1 (GPIO)*/
  PORTB_PCR22 = 0x100 ;	/*Red Led, configured as Alternative 1 (GPIO)*/
  GPIOB_PDDR |= (1 << 21) ; /*Setting the bit 21 of the port B as Output*/
  GPIOB_PDDR |= (1 << 22) ; /*Setting the bit 22 of the port B as Output*/
  GPIOB_PDOR |= (1 << 21) ; /*Turn Off Blue Led*/
  GPIOB_PDOR |= (1 << 22) ; /*Turn Off Red Led*/
}

void lightUpLED(void){
	GPIOB_PDOR = (1 << 22);/*Turn On Blue Led*/
	Delay(delay) ;
	GPIOB_PDOR = (1 << 21) | (1 << 22); /*Turn Off Blue Led*/
	Delay(delay) ;
}

void readIRQ(void){
	unsigned char readPortD ;
	readPortD = 0x01 & GPIOD_PDIR ;
	while(readPortD == 0x01){
		__asm("nop") ;
	}
}

/*
 *	///////////////////////////////
 *	TODO:
 *		1. fix IRQ function
 *		2. fix algorithm function to correctly display HR and SpO2
 *  ///////////////////////////////
*/

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  uint32_t un_min, un_max, un_prev_data ;
  int32_t n_brightness ;
  int i ;
  float f_temp ;
  int len ;		// length of string

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  // initialize on board LED
  initLED() ;

  // restart the MAX30102
   maxim_max30102_reset() ;
  // wait ~ 1 [s]
  Delay(delay) ;
  // read and clear status register
  maxim_max30102_read_reg(0, &uch_dummy) ;

  maxim_max30102_init() ;

  n_brightness = 0 ;
  un_min = 0x3FFFF ;
  un_max = 0 ;

  n_ir_buffer_length = 500 ;		// stores 100 values per second for 5 seconds

  // print test to console
  printf("\nHello ... test\n") ;

  // read first 500 samples
  for(i = 0; i < n_ir_buffer_length; i++){
	  // wait until PTD1 asserts
	  //readIRQ() ;

	  // read from FIFO
	  maxim_max30102_read_fifo((aun_red_buffer + i), (aun_ir_buffer + i)) ;
	  // update min/max values
	  if(un_min > aun_red_buffer[i]){
		un_min = aun_red_buffer[i];    //update signal min
	  }
	  if(un_max < aun_red_buffer[i]){
		un_max = aun_red_buffer[i];    //update signal max
	  }
  }
  un_prev_data = aun_red_buffer[i] ;

  // calculate heart rate and SpO2 for first 500 samples
  maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer,
		  	  	  	  	  	  	  	  	 &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid) ;

  // continuously take samples from MAX30102. Heart rate and SpO2 calculated every second
  while(1){
	  lightUpLED() ;

	  i = 0 ;
	  un_min = 0x3FFFF ;
	  un_max = 0 ;

	  // erase first 100 sets of data
	  for(i = 100; i < 500; i++){
		  aun_red_buffer[i - 100] = aun_red_buffer[i] ;
		  aun_ir_buffer[i - 100] = aun_ir_buffer[i] ;

		  // update signal for min/max
		  if(un_min > aun_red_buffer[i]){
			  un_min = aun_red_buffer[i] ;
		  }
		  if(un_max < aun_red_buffer[i]){
			  un_max = aun_red_buffer[i] ;
		  }
	  }

	  // take 100 sets of samples before calculating heart rate
	  for(i = 400 ; i < 500; i++){
		  un_prev_data = aun_red_buffer[i - 1] ;
		  // interrupt function
		  //readIRQ() ;

		  maxim_max30102_read_fifo((aun_red_buffer + i), (aun_ir_buffer + i)) ;

		  if(aun_red_buffer[i] > un_prev_data) {
			  f_temp = aun_red_buffer[i] - un_prev_data ;
			  f_temp /= (un_max - un_min) ;
			  f_temp *= MAX_BRIGHTNESS ;
			  n_brightness -= (int)f_temp ;
			  // check brightness value
			  if(n_brightness < 0){
				  n_brightness = 0 ;
			  }
		  }
		  else {
			  f_temp = un_prev_data - aun_red_buffer[i] ;
			  f_temp /= (un_max - un_min) ;
			  f_temp *= MAX_BRIGHTNESS ;
			  n_brightness += (int)f_temp ;
			  if(n_brightness > MAX_BRIGHTNESS){
				  n_brightness = MAX_BRIGHTNESS ;
			  }
		  }
		  // print heart rate and SpO2 to terminal
		  if(i == 499){ printf("Heart rate: %i SpO2: %i\n", n_heart_rate, n_sp02) ; }
		  //Delay(delay) ;
	  }

	  // call heart rate and oxygen saturation function
	  maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer,
			  	  	  	  	  	  	  	  	 &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid) ;
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
