/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Vectors.c
**     Project     : HCU_V0.2
**     Processor   : MC9S08DZ60MLH
**     Version     : Component 01.076, Driver 01.40, CPU db: 3.00.026
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2017-05-18, 09:06, # CodeGen: 7
**     Abstract    :
**         This component "MC9S08DZ60_64" contains initialization 
**         of the CPU and provides basic methods and events for 
**         CPU core settings.
**     Settings    :
**
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
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
** @file Vectors.c                                                  
** @version 01.40
** @brief
**         This component "MC9S08DZ60_64" contains initialization 
**         of the CPU and provides basic methods and events for 
**         CPU core settings.
*/         
/*!
**  @addtogroup Vectors_module Vectors module documentation
**  @{
*/         


#include "Cpu.h"
#include "CAN.h"
#include "WDog_1S.h"
#include "ADCH.h"
#include "SPI_DriverSS_1.h"
#include "SPI.h"
#include "SPI_DriverSS_2.h"
#include "SPI_DriverINH_1.h"
#include "SPI_DriverFault_1.h"
#include "SPI_DriverFault_2.h"
#include "SPI_DriverINH_2.h"
#include "TI_1ms.h"
#include "TI_20ms.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "LED4.h"

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
static void (* near const _vect[])(void) @0xFFC0 = { /* Interrupt vector table */
/*lint -restore Enable MISRA rule (1.1) checking. */
         Cpu_Interrupt,                /* Int.no. 31 Vacmp2 (at FFC0)                Unassigned */
         Cpu_Interrupt,                /* Int.no. 30 Vacmp1 (at FFC2)                Unassigned */
         CAN_InterruptTx,              /* Int.no. 29 Vcantx (at FFC4)                Used */
         CAN_InterruptRx,              /* Int.no. 28 Vcanrx (at FFC6)                Used */
         CAN_InterruptError,           /* Int.no. 27 Vcanerr (at FFC8)               Used */
         Cpu_Interrupt,                /* Int.no. 26 Vcanwu (at FFCA)                Unassigned */
         TI_1ms_Interrupt,             /* Int.no. 25 Vrtc (at FFCC)                  Used */
         Cpu_Interrupt,                /* Int.no. 24 Viic (at FFCE)                  Unassigned */
         ADCH_Interrupt,               /* Int.no. 23 Vadc (at FFD0)                  Used */
         Cpu_Interrupt,                /* Int.no. 22 Vport (at FFD2)                 Unassigned */
         Cpu_Interrupt,                /* Int.no. 21 Vsci2tx (at FFD4)               Unassigned */
         Cpu_Interrupt,                /* Int.no. 20 Vsci2rx (at FFD6)               Unassigned */
         Cpu_Interrupt,                /* Int.no. 19 Vsci2err (at FFD8)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 18 Vsci1tx (at FFDA)               Unassigned */
         Cpu_Interrupt,                /* Int.no. 17 Vsci1rx (at FFDC)               Unassigned */
         Cpu_Interrupt,                /* Int.no. 16 Vsci1err (at FFDE)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 15 Vspi (at FFE0)                  Unassigned */
         Cpu_Interrupt,                /* Int.no. 14 Vtpm2ovf (at FFE2)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 13 Vtpm2ch1 (at FFE4)              Unassigned */
         TI_20ms_Interrupt,            /* Int.no. 12 Vtpm2ch0 (at FFE6)              Used */
         Cpu_Interrupt,                /* Int.no. 11 Vtpm1ovf (at FFE8)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 10 Vtpm1ch5 (at FFEA)              Unassigned */
         Cpu_Interrupt,                /* Int.no.  9 Vtpm1ch4 (at FFEC)              Unassigned */
         Cpu_Interrupt,                /* Int.no.  8 Vtpm1ch3 (at FFEE)              Unassigned */
         Cpu_Interrupt,                /* Int.no.  7 Vtpm1ch2 (at FFF0)              Unassigned */
         Cpu_Interrupt,                /* Int.no.  6 Vtpm1ch1 (at FFF2)              Unassigned */
         Cpu_Interrupt,                /* Int.no.  5 Vtpm1ch0 (at FFF4)              Unassigned */
         Cpu_Interrupt,                /* Int.no.  4 Vlol (at FFF6)                  Unassigned */
         Cpu_Interrupt,                /* Int.no.  3 Vlvd (at FFF8)                  Unassigned */
         Cpu_Interrupt,                /* Int.no.  2 Virq (at FFFA)                  Unassigned */
         Cpu_Interrupt,                /* Int.no.  1 Vswi (at FFFC)                  Unassigned */
         _EntryPoint                   /* Int.no.  0 Vreset (at FFFE)                Reset vector */
};
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/

