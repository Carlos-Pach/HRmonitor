/** ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Cpu.c
**     Project     : HRmonitor
**     Processor   : MK64FN1M0VLL12
**     Component   : MK64FN1M0LL12
**     Version     : Component 01.046, Driver 01.00, CPU db: 3.00.000
**     Repository  : Kinetis
**     Datasheet   : K64P144M120SF5RM, Rev.2, January 2014
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-08-20, 19:28, # CodeGen: 25
**     Abstract    :
**
**     Settings    :
**
**     Contents    :
**         SetClockConfiguration - LDD_TError Cpu_SetClockConfiguration(LDD_TClockConfiguration ModeID);
**         GetClockConfiguration - LDD_TClockConfiguration Cpu_GetClockConfiguration(void);
**
**     (c) Freescale Semiconductor, Inc.
**     2004 All Rights Reserved
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
** @file Cpu.c
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup Cpu_module Cpu module documentation
**  @{
*/         

/* MODULE Cpu. */

/* {Default RTOS Adapter} No RTOS includes */
#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
** ===================================================================
**     Method      :  Common_Init (component MK64FN1M0LL12)
**     Description :
**         Initialization of registers for that there is no 
**         initialization component.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if CPU_COMMON_INIT
void Common_Init(void)
{
  /* Common initialization of registers which initialization is required 
     for proper functionality of components in the project but initialization
     component which would be configuring these registers is missing 
     in the project. 
     Add associated initialization component to the project to avoid 
     initialization of registers in the Common_Init().
     Also, after reset value optimization property affects initialization of 
     registers in this method (see active generator configuration 
     Optimizations\Utilize after reset values property or enabled processor 
     component Common settings\Utilize after reset values property) */
  /* Enable clock gate of peripherals initialized in Common_Init() */
  /* SIM_SCGC5: PORTE=1,PORTD=1 */
  SIM_SCGC5 |= (SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTD_MASK);

  /* SIM_SCGC5: PORTD=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
  /* NVICIP62: PRI62=0 */
  NVICIP62 = NVIC_IP_PRI62(0x00);
  /* PORTD_DFCR: CS=0 */
  PORTD_DFCR &= (uint32_t)~(uint32_t)(PORT_DFCR_CS_MASK);
  /* PORTD_DFWR: FILT=0 */
  PORTD_DFWR &= (uint32_t)~(uint32_t)(PORT_DFWR_FILT(0x1F));
  /* PORTD_PCR1: ISF=0,IRQC=0,LK=0,PE=1,PS=1 */
  PORTD_PCR1 = (uint32_t)((PORTD_PCR1 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_IRQC(0x0F) |
                PORT_PCR_LK_MASK
               )) | (uint32_t)(
                PORT_PCR_PE_MASK |
                PORT_PCR_PS_MASK
               ));
  /* PORTE_PCR24: ISF=0,MUX=5 */
  PORTE_PCR24 = (uint32_t)((PORTE_PCR24 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x02)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x05)
                ));
  /* PORTE_PCR25: ISF=0,MUX=5 */
  PORTE_PCR25 = (uint32_t)((PORTE_PCR25 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x02)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x05)
                ));

  /* Disable clock gate of peripherals initialized in Common_Init() */
  /* SIM_SCGC5: PORTE=0 */
  SIM_SCGC5 &= (uint32_t)~(uint32_t)(SIM_SCGC5_PORTE_MASK);
}

#endif /* CPU_COMMON_INIT */

/*
** ===================================================================
**     Method      :  Components_Init (component MK64FN1M0LL12)
**     Description :
**         Initialization of components (with exception for Peripheral
**         Initialization Components which are initialized in 
**         Peripherals_Init() method).
**         For example, if automatic initialization feature 
**         is enabled in LDD component then its Init method call 
**         is executed in Components_Init() method.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#if CPU_COMPONENTS_INIT
void Components_Init(void)
{
  MCUC1_Init(); /* ### McuLibConfig "MCUC1" init code ... */
  WAIT1_Init(); /* ### Wait "WAIT1" init code ... */
  GI2C1_Init(); /* ### GenericI2C "GI2C1" init code ... */
}
#endif /* CPU_COMPONENTS_INIT */

/*
** ===================================================================
**     Method      :  Cpu_INT_NMIInterrupt (component MK64FN1M0LL12)
**
**     Description :
**         This ISR services the Non Maskable Interrupt interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(Cpu_INT_NMIInterrupt)
{
  Cpu_OnNMI();
}


#ifdef __cplusplus
}
#endif

/* END Cpu. */

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
