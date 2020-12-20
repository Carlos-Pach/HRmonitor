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
#include "CLS1.h"
#include "UTIL1.h"
#include "CS1.h"
#include "XF1.h"
#include "BT1.h"
#include "Serial1.h"
#include "ASerialLdd1.h"
#include "EInt1.h"
#include "ExtIntLdd1.h"
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
#define BAUD_RATE 		38400

/* declare function prototypes */
void initBT(void) ;
void Delay(unsigned long delay) ;
void initLED(void) ;

uint32_t aun_ir_buffer[BUFFER_SIZE] ;	// IR LED sensor data
int32_t n_ir_buffer_length ;		// data length
uint32_t aun_red_buffer[BUFFER_SIZE] ;	// red LED sensor data
int32_t n_sp02 ;					// SPO2 value
int8_t ch_spo2_valid ;				// indicator to show if SPO02 calculation is valid
int32_t n_heart_rate ;				// heart rate value
int8_t ch_hr_valid ;				// indicator to show if heart rate calculation is valid
uint8_t uch_dummy ;					// char used to get keyboard input ... might remove

volatile unsigned char readPortD ;

volatile unsigned long delay = 0x10000 ;

void Delay(unsigned long delay){
	while(delay > 0) delay-- ;
}


/*
 *	Function name: initBT
 *	Purpose: Initializes the BT module
 *
 *	Parameters: None
 *	Return values: None
*/
void initBT(void){
	/* init the BT module */
	//BT1_Init() ;
	/* declare baud rate for BT module */
	BT1_btSetBaud(BAUD_RATE) ;
	/* send char to BT module */
	BT1_SendChar('C') ;
}


/* light up on-board LED to notify user the system is initialized and active */
void initLED(void){
  // set up on-board LED for testing
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Enable Port B Clock Gate Control*/
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK ; /* Enable Port D Clock Gate Control*/

  /* set up PORTD[3, 1] as GPIO */
  /* set up in processor expert done */
  /* set up PORTD[3, 1] as input */
  /* set up in processor expert done */
  /* configure PD3, PD1 to trigger interrupt on falling edge */
  //PORTD_PCR1 = 0xA100 ;
  //PORTD_PCR3 = 0xA100 ;
  /* clear ISFR on PD1 and PD3 */
  //PORTD_ISFR = 0xFFFFFFFF ;
  /* enable interrupts */


  // set up PORTB[22:21, 1] for GPIO
  PORTB_GPCLR = 0x00040100 ; 	// set up PORTB[2] as GPIO
  PORTB_GPCHR = 0x00C00100 ;	// set up PORTB[22:21] as GPIO
  // set up PORTB[22:21] as output
  GPIOB_PDDR = 0x00600000 ;	// 0x00C... --> 0x006
}


void PORTB_ISR(void){
	// turn off LEDs
	GPIOB_PDOR |= (1 << 22);
	GPIOB_PDOR |= (1 << 21) ;
	// create var to read from PORTB[1]
	uint8_t readPortB ;
	readPortB = 0x0F & GPIOB_PDIR ;	// 0x04 --> 0x0F

	/* 		Switch statement conditions:
	 * 			a. DIP switch is an open circuit/off: output red-LED on console
	 * 			b. DIP switch is a closed circuit/on: output multi-LED on console
	 * 			c. default it to off
	 */
	switch(readPortB){
		case 0x04:	/* turn on LED mode */
			maxim_max30102_mode_change(0x09, 0x02) ;	// 0x02 red only
			printf("Switch mode: red-LED\n") ;
			break ;
		case 0x00 :	/* turn on SpO2 mode */
			maxim_max30102_mode_change(0x09, 0x03) ;	// 0x03 SpO2 only
			printf("Switch mode: SpO2\n") ;
			break ;
		default:	/* turn on LED mode */
			maxim_max30102_mode_change(0x09, 0x02) ;	// 0x02 red only
			printf("Switch mode: red-LED\n") ;
			break ;
	}
	for(int i = 0; i < 10; i++) ;	// simple debounce code
}


/*
 *	///////////////////////////////
 *	TODO:
 *		1. fix IRQ functions
 *			a. fix for INT pin on max30102
 *				i. INT pin from MAX30102 always outputting ~3.1 [V]
*			b. DIP switch
*				i. pin always entering ISR
 *		2. fix algorithm function to correctly display HR and SpO2
 *			a. Displays incorrect values when finger is placed
 *		3. connect hc-06 to phone for bluetooth connection
 *			a. connects but doesn't send data
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

  /* begin initialization of peripherals */
  initLED() ;	/* initialize on board LED and GPIO pins */
  initBT() ;	/* initialize the BT module */

  maxim_max30102_reset() ; /* restart the max30102 */
  Delay(delay) ;	/* wait ~1 [s] */
  maxim_max30102_read_reg(0, &uch_dummy) ; /* read and clear status register */

  maxim_max30102_init() ;	/* initialize max30102 */
  /* end initialization of peripherals */


  n_brightness = 0 ;
  un_min = 0x3FFFF ;
  un_max = 0 ;

  n_ir_buffer_length = 500 ;		// stores 100 values per second for 5 seconds

  printf("\nHello ... test\n") ;	/* test output to console */

  // read first 500 samples
  for(i = 0; i < n_ir_buffer_length; i++){
	  // read PORTD[1]
	  readPortD = GPIOD_PDIR & 0x0F ;
	  // wait until PTD1 asserts
	  //while(readPortD == 0x02){ PORTD_ISR() ; }

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
	  BT1_SendChar('C') ;	/* test BT module */

	  i = 0 ;
	  un_min = 0x3FFFF ;
	  un_max = 0 ;

	  //PORTB_ISR() ;		// see if switch is flipped

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

		  // read PORTD[1]
		  //readPortD = GPIOD_PDIR & 0x0F ;	/* GPIOD_PDIR[1]: 0b0010 if reading */
		  //while(!EInt1_GetVal()) ; /* while interrupt is on */
		  /* print interrupt val to console */
		  //printf("interrupt getVal: %d\n", (int)EInt1_GetVal()) ;
		  // wait until PTD1 asserts
		  //while(readPortD == 0x02){ PORTD_ISR() ; }

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
	  }

	  // call heart rate and oxygen saturation function
	  maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer,
			  	  	  	  	  	  	  	  	 &n_sp02, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid) ;
	  printf("HR valid: %i SpO2 valid: %i ", ch_hr_valid, ch_spo2_valid) ;
	  printf("Heart rate: %i SpO2: %i\n", n_heart_rate, n_sp02) ;
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
