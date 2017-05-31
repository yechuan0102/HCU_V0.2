/* ###################################################################
**     Filename    : Events.c
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
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
static unsigned char watchpoint = 0;
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
void ADCH_OnEnd(void)
{
	/* Write your code here ... */
	Task_ADCHS = 1;
}


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
void CAN_OnFreeTxBuffer(word BufferMask)
{
	/* Write your code here ... */
	if (BufferMask == 0)
	{
		PrtCANTXD = 0;
		DisableCANTXD;
		return;
	}
	if (PrtCANTXD<CAN_TXD_NUM)
	{
		watchpoint = CAN_SendFrameExt(CAN_EXTENDED_FRAME_ID | (Msg_CAN_TXD[PrtCANTXD].ID.ID), Msg_CAN_TXD[PrtCANTXD].FrameType, Msg_CAN_TXD[PrtCANTXD].length, &(Msg_CAN_TXD[PrtCANTXD].data[0]));
		PrtCANTXD++;
	}
	else
	{
		PrtCANTXD = 0;
		CANTIER &= (unsigned char)(~BufferMask);
	}
}

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
void CAN_OnFullRxBuffer(void)
{
	/* Write your code here ... */
	CANDownLoad();
}

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
void CAN_OnBusOff(void)
{
  /* Write your code here ... */
	CAN_Init();
	CANMsgBuffersConfig();
}

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
void TI_1ms_OnInterrupt(void)
{
	/* Write your code here ... */
	Timer_CAN++;
	if (Timer_CAN>=CAN_Send_Delay)
	{
		Task_CANTXD = 1;
		(void)TI_1ms_Disable();
		Timer_CAN = 0;
	}
}

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
void TI_20ms_OnInterrupt(void)
{
  /* Write your code here ... */
	Timer_100ms++;
	if (Timer_100ms == 5)
	{
		Timer_100ms = 0;
		Task_TLE6232 = 1;
	}
	Task_ADreStart = 1;
	Task_ErrorDiagnosis = 1;
}

/* END Events */

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
