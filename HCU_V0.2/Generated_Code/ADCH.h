/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : ADCH.h
**     Project     : HCU_V0.2
**     Processor   : MC9S08DZ60MLH
**     Component   : ADC
**     Version     : Component 01.690, Driver 01.30, CPU db: 3.00.026
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2017-05-18, 19:05, # CodeGen: 11
**     Abstract    :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**          Component name                                 : ADCH
**          A/D converter                                  : ADC
**          Sharing                                        : Disabled
**          Interrupt service/event                        : Enabled
**            A/D interrupt                                : Vadc
**            A/D interrupt priority                       : low priority
**          A/D channels                                   : 13
**            Channel0                                     : 
**              A/D channel (pin)                          : PTA0_PIA0_ADP0_MCLK
**              A/D channel (pin) signal                   : 
**            Channel1                                     : 
**              A/D channel (pin)                          : PTA1_PIA1_ADP1_ACMP1PLUS
**              A/D channel (pin) signal                   : 
**            Channel2                                     : 
**              A/D channel (pin)                          : PTA2_PIA2_ADP2_ACMP1MINUS
**              A/D channel (pin) signal                   : 
**            Channel3                                     : 
**              A/D channel (pin)                          : PTA3_PIA3_ADP3_ACMP1O
**              A/D channel (pin) signal                   : 
**            Channel4                                     : 
**              A/D channel (pin)                          : PTA4_PIA4_ADP4
**              A/D channel (pin) signal                   : 
**            Channel5                                     : 
**              A/D channel (pin)                          : PTA5_PIA5_ADP5
**              A/D channel (pin) signal                   : 
**            Channel6                                     : 
**              A/D channel (pin)                          : PTA6_PIA6_ADP6
**              A/D channel (pin) signal                   : 
**            Channel7                                     : 
**              A/D channel (pin)                          : PTA7_PIA7_ADP7_IRQ
**              A/D channel (pin) signal                   : 
**            Channel8                                     : 
**              A/D channel (pin)                          : PTB0_PIB0_ADP8
**              A/D channel (pin) signal                   : 
**            Channel9                                     : 
**              A/D channel (pin)                          : PTB1_PIB1_ADP9
**              A/D channel (pin) signal                   : 
**            Channel10                                    : 
**              A/D channel (pin)                          : PTB2_PIB2_ADP10
**              A/D channel (pin) signal                   : 
**            Channel11                                    : 
**              A/D channel (pin)                          : PTB3_PIB3_ADP11
**              A/D channel (pin) signal                   : 
**            Channel12                                    : 
**              A/D channel (pin)                          : PTB4_PIB4_ADP12
**              A/D channel (pin) signal                   : 
**          A/D resolution                                 : 12 bits
**          Conversion time                                : 23 ?s
**          Low-power mode                                 : Disabled
**          Sample time                                    : long
**          External trigger                               : Disabled
**          Internal trigger                               : Disabled
**          Number of conversions                          : 8
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**          High input limit                               : 1
**          Low input limit                                : 0
**          Get value directly                             : yes
**          Wait for result                                : yes
**     Contents    :
**         Enable   - byte ADCH_Enable(void);
**         Disable  - byte ADCH_Disable(void);
**         Start    - byte ADCH_Start(void);
**         Stop     - byte ADCH_Stop(void);
**         Measure  - byte ADCH_Measure(bool WaitForResult);
**         GetValue - byte ADCH_GetValue(void* Values);
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
** @file ADCH.h
** @version 01.30
** @brief
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup ADCH_module ADCH module documentation
**  @{
*/         

#ifndef __ADCH
#define __ADCH

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* MODULE ADCH. */

#include "Cpu.h"




__interrupt void ADCH_Interrupt(void);
/*
** ===================================================================
**     Method      :  ADCH_Interrupt (component ADC)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void ADCH_HWEnDi(void);
/*
** ===================================================================
**     Method      :  ADCH_HWEnDi (component ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


byte ADCH_Enable(void);
/*
** ===================================================================
**     Method      :  ADCH_Enable (component ADC)
*/
/*!
**     @brief
**         Enables A/D converter component. [Events] may be generated
**         ([DisableEvent]/[EnableEvent]). If possible, this method
**         switches on A/D converter device, voltage reference, etc.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/

byte ADCH_Disable(void);
/*
** ===================================================================
**     Method      :  ADCH_Disable (component ADC)
*/
/*!
**     @brief
**         Disables A/D converter component. No [events] will be
**         generated. If possible, this method switches off A/D
**         converter device, voltage reference, etc.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/

byte ADCH_Start(void);
/*
** ===================================================================
**     Method      :  ADCH_Start (component ADC)
*/
/*!
**     @brief
**         This method starts continuous conversion on all channels
**         that are set in the component inspector. When each
**         measurement on all channels has finished the [OnEnd ] event
**         may be invoked. This method is not available if the
**         [interrupt service] is disabled and the device doesn't
**         support the continuous mode. Note: If time of measurement is
**         too short and the instruction clock is too slow then the
**         conversion complete interrupt and its handler may cause a
**         system overflow.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
*/
/* ===================================================================*/

byte ADCH_Stop(void);
/*
** ===================================================================
**     Method      :  ADCH_Stop (component ADC)
**     Description :
**         This method stops the continuous measurement or disables
**         a trigger mode (if supported by HW), which has been
**         started by one of the following methods:
**         Version specific information for Freescale HCS08 and HC08
**         derivatives ] 
**         - <Start> 
**         - <EnableIntChanTrigger>
**         - <EnableExtChanTrigger>
**         The Stop method is available if one of the previously
**         mentioned methods is supported by A/D converter device
**         and is enabled to be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_BUSY - No continuous measurement is
**                           running. Neither internal trigger nor
**                           external trigger have been enabled (if
**                           these are supported by HW).
** ===================================================================
*/

byte ADCH_Measure(bool WaitForResult);
/*
** ===================================================================
**     Method      :  ADCH_Measure (component ADC)
*/
/*!
**     @brief
**         This method performs one measurement on all channels that
**         are set in the component inspector. (Note: If the [number of
**         conversions] is more than one the conversion of A/D channels
**         is performed specified number of times.)
**     @param
**         WaitForResult   - Wait for a result of a
**                           conversion. If [interrupt service] is
**                           disabled, A/D peripheral doesn't support
**                           measuring all channels at once or Autoscan
**                           mode property isn't enabled and at the same
**                           time the [number of channels] is greater
**                           than 1, then the WaitForResult parameter is
**                           ignored and the method waits for each
**                           result every time. If the [interrupt
**                           service] is disabled and a [number of
**                           conversions] is greater than 1, the
**                           parameter is ignored and the method also
**                           waits for each result every time.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
*/
/* ===================================================================*/

byte ADCH_GetValue(void *Values);
/*
** ===================================================================
**     Method      :  ADCH_GetValue (component ADC)
*/
/*!
**     @brief
**         Returns the last measured values for all channels. Format
**         and width of the value is a native format of the A/D
**         converter.
**     @param
**         Values          - Pointer to the array that contains
**                           the measured data. Data type is a byte, a
**                           word or an int. It depends on the supported
**                           modes, resolution, etc. of the AD converter.
**                           See the Version specific information for
**                           the current CPU in [General Info].
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
*/
/* ===================================================================*/

void ADCH_Init(void);
/*
** ===================================================================
**     Method      :  ADCH_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the component's 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/



/* END ADCH. */

#endif /* ifndef __ADCH */
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
