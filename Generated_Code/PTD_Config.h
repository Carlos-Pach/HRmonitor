/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : PTD_Config.h
**     Project     : HRmonitor
**     Processor   : MK64FN1M0VLL12
**     Component   : Init_GPIO
**     Version     : Component 01.006, Driver 01.06, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-12-15, 15:02, # CodeGen: 78
**     Abstract    :
**          This file implements the GPIO (PTD) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
**     Settings    :
**          Component name                                 : PTD
**          Device                                         : PTD
**          Settings                                       : 
**            Clock gate                                   : Enabled
**            Pin 0                                        : Do not initialize
**            Pin 1                                        : Initialize
**              Pin direction                              : Input
**              Output value                               : 1
**              Open drain                                 : <Automatic>
**              Pull resistor                              : Disabled
**              Pull selection                             : Pull Down
**              Slew rate                                  : <Automatic>
**              Drive strength                             : <Automatic>
**              Interrupt/DMA request                      : Disabled
**              Digital filter                             : <Automatic>
**              Passive filter                             : <Automatic>
**              Lock                                       : <Automatic>
**            Pin 2                                        : Do not initialize
**            Pin 3                                        : Do not initialize
**            Pin 4                                        : Do not initialize
**            Pin 5                                        : Do not initialize
**            Pin 6                                        : Do not initialize
**            Pin 7                                        : Do not initialize
**            Digital filter clock source                  : <Automatic>
**            Digital filter width                         : <Automatic>
**          Pin selection/routing                          : 
**            Pin 0                                        : Disabled
**            Pin 1                                        : Enabled
**              Pin                                        : J2_12
**            Pin 2                                        : Disabled
**            Pin 3                                        : Disabled
**            Pin 4                                        : Disabled
**            Pin 5                                        : Disabled
**            Pin 6                                        : Disabled
**            Pin 7                                        : Disabled
**          Interrupts                                     : 
**            Port interrupt                               : Enabled
**              Interrupt                                  : INT_PORTD
**              Interrupt request                          : Enabled
**              Interrupt priority                         : <Automatic>
**              ISR Name                                   : PORTD_ISR
**          Initialization                                 : 
**            Call Init method                             : yes
**            Utilize after reset values                   : default
**     Contents    :
**         Init - void PTD_Init(void);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file PTD_Config.h                                                  
** @version 01.06
** @brief
**          This file implements the GPIO (PTD) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
*/         
/*!
**  @addtogroup PTD_Config_module PTD_Config module documentation
**  @{
*/         

#ifndef PTD_Config_H_
#define PTD_Config_H_

/* MODULE PTD. */

/* GPIOD_PSOR: PTSO|=2 */
#define GPIOD_PSOR_VALUE     0x02U
#define GPIOD_PSOR_MASK      0x02U
/* GPIOD_PCOR: PTCO&=~2 */
#define GPIOD_PCOR_VALUE     0x00U
#define GPIOD_PCOR_MASK      0x02U
/* GPIOD_PDDR: PDD&=~2 */
#define GPIOD_PDDR_VALUE     0x00U
#define GPIOD_PDDR_MASK      0x02U



#define PTD_AUTOINIT

#define INT_PORTD_ISR PORTD_ISR

/* END PTD. */
#endif /* #ifndef __PTD_Config_H_ */
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
