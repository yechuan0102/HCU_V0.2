/* ###################################################################
**     Filename    : Events.h
**     Project     : HCU_V0.01
**     Processor   : MC9S08DZ60MLH
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2017-04-05, 14:07, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "CAN.h"
#include "WDog_1S.h"
#include "ADCH.h"
#include "SPI.h"
#include "SPI_DriverSS_1.h"
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
#include "includes.h"

void ADCH_OnEnd(void);
/*
** ===================================================================
**     Event       :  ADCH_OnEnd (module Events)
**
**     Component   :  ADCH [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void CAN_OnFreeTxBuffer(word BufferMask);
/*
** ===================================================================
**     Event       :  CAN_OnFreeTxBuffer (module Events)
**
**     Component   :  CAN [FreescaleCAN]
**     Description :
**         This event is called after a successful transmission of a
**         message. The event is available only if Interrupt
**         service/event is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**         BufferMask      - Transmit buffer mask. The
**                           mask can be used to check what message
**                           buffer caused the transmit interrupt.
**     Returns     : Nothing
** ===================================================================
*/

void CAN_OnFullRxBuffer(void);
/*
** ===================================================================
**     Event       :  CAN_OnFullRxBuffer (module Events)
**
**     Component   :  CAN [FreescaleCAN]
**     Description :
**         This event is called when the receive buffer is full after a
**         successful reception of a message. The event is available
**         only if Interrupt service/event is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void CAN_OnBusOff(void);
/*
** ===================================================================
**     Event       :  CAN_OnBusOff (module Events)
**
**     Component   :  CAN [FreescaleCAN]
**     Description :
**         This event is called when the node status becomes bus-off.
**         The event is available only if Interrupt service/event is
**         enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TI_1ms_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  TI_1ms_OnInterrupt (module Events)
**
**     Component   :  TI_1ms [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TI_20ms_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  TI_20ms_OnInterrupt (module Events)
**
**     Component   :  TI_20ms [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

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
