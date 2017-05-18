/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : SPI.c
**     Project     : HCU_V0.2
**     Processor   : MC9S08DZ60MLH
**     Component   : SynchroMaster
**     Version     : Component 02.347, Driver 01.30, CPU db: 3.00.026
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2017-05-18, 09:06, # CodeGen: 7
**     Abstract    :
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
**     Settings    :
**         Synchro type                : MASTER
**
**         Serial channel              : SPI
**
**         Protocol
**             Init baud rate          : 2us
**             Clock edge              : rising
**             Width                   : 8 bits (always)
**             Empty character         : 0
**             Empty char. on input    : RECEIVED
**
**         Registers
**             Input buffer            : SPID      [$0055]
**             Output buffer           : SPID      [$0055]
**             Control register        : SPIC1     [$0050]
**             Mode register           : SPIC2     [$0051]
**             Baud setting reg.       : SPIBR     [$0052]
**
**
**
**         Used pins                   :
**         ----------------------------------------------------------
**              Function    | On package |    Name
**         ----------------------------------------------------------
**               Input      |     20     |  PTE5_SDA_MISO
**               Output     |     19     |  PTE4_SCL_MOSI
**               Clock      |     18     |  PTE3_SPSCK
**         ----------------------------------------------------------
**
**     Contents    :
**         RecvChar        - byte SPI_RecvChar(SPI_TComData *Chr);
**         SendChar        - byte SPI_SendChar(SPI_TComData Chr);
**         CharsInRxBuf    - byte SPI_CharsInRxBuf(word *Chr);
**         GetCharsInRxBuf - word SPI_GetCharsInRxBuf(void);
**         CharsInTxBuf    - byte SPI_CharsInTxBuf(word *Chr);
**         GetCharsInTxBuf - word SPI_GetCharsInTxBuf(void);
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
** @file SPI.c
** @version 01.30
** @brief
**         This component "SynchroMaster" implements MASTER part of synchronous
**         serial master-slave communication.
*/         
/*!
**  @addtogroup SPI_module SPI module documentation
**  @{
*/         


/* MODULE SPI. */

#include "SPI.h"
#include "CAN.h"
#include "WDog_1S.h"
#include "ADCH.h"
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


/* Internal method prototypes */

#define OVERRUN_ERR      0x01U         /* Overrun error flag bit   */
#define CHAR_IN_RX       0x08U         /* Char is in RX buffer     */
#define FULL_TX          0x10U         /* Full transmit buffer     */
#define RUNINT_FROM_TX   0x20U         /* Interrupt is in progress */
#define FULL_RX          0x40U         /* Full receive buffer      */


/*
** ===================================================================
**     Method      :  SPI_RecvChar (component SynchroMaster)
**     Description :
**         If any data is received, this method returns one character,
**         otherwise it returns an error code (it does not wait for
**         data). 
**         For information about SW overrun behavior please see
**         <General info page>.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - A pointer to the received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK - The valid data is received.
**                           ERR_SPEED - This device does not work in
**                           the active speed mode.
**                           ERR_RXEMPTY - No data in receiver.
**                           ERR_OVERRUN - Overrun error was detected
**                           from the last char or block received. In
**                           polling mode, this error code is returned
**                           only when the hardware supports detection
**                           of the overrun error. If interrupt service
**                           is enabled, and input buffer allocated by
**                           the component is full, the component
**                           behaviour depends on <Input buffer size>
**                           property : if property is 0, last received
**                           data-word is preserved (and previous is
**                           overwritten), if property is greater than 0,
**                           new received data-word are ignored.
**                           ERR_FAULT - Fault error was detected from
**                           the last char or block received. In the
**                           polling mode the ERR_FAULT is return until
**                           the user clear the fault flag bit, but in
**                           the interrupt mode ERR_FAULT is returned
**                           only once after the fault error occured.
**                           This error is supported only on the CPUs
**                           supports the faul mode function - where
**                           <Fault mode> property is available.
** ===================================================================
*/
/*
byte SPI_RecvChar(SPI_TComData *Chr)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  SPI_SendChar (component SynchroMaster)
**     Description :
**         Sends one character to the channel.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled (only if
**                           output DMA is supported and enabled)
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/
/*
byte SPI_SendChar(SPI_TComData Chr)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  SPI_CharsInRxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the input buffer.
**         Note: If the Interrupt service is disabled, and the Ignore
**         empty character is set to yes, and a character has been
**         received, then this method returns 1 although it was an
**         empty character.
**         (deprecated method - Use the GetCharsInRxBuf method instead!)
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - A pointer to number of characters in the
**                           input buffer
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte SPI_CharsInRxBuf(word *Chr)
{
  *Chr = (word) SPIS_SPRF;             /* Return number of chars in the receive buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SPI_GetCharsInRxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the input buffer.
**         Note: If the Interrupt service is disabled, and the Ignore
**         empty character is set to yes, and a character has been
**         received, then this method returns 1 although it was an
**         empty character.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the input buffer.
** ===================================================================
*/
/*
word SPI_GetCharsInRxBuf(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  SPI_CharsInTxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the output buffer.
**         (deprecated method - Use the GetCharsInRxBuf method instead!)
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - A pointer to the number of characters in
**                           the output buffer
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte SPI_CharsInTxBuf(word *Chr)
{
  *Chr = (SPIS_SPTEF ? (word)0U : (word)1U); /* Return number of chars in the transmit buffer */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SPI_GetCharsInTxBuf (component SynchroMaster)
**     Description :
**         Returns the number of characters in the output buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the output buffer.
** ===================================================================
*/
/*
word SPI_GetCharsInTxBuf(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  SPI_Init (component SynchroMaster)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void SPI_Init(void)
{
  #pragma MESSAGE DISABLE C4002        /* Disable warning C4002 "Result not used" */
  (void)SPIS;                          /* Read the status register */
  (void)SPID;                          /* Read the data register */
  /* SPIBR: ??=0,SPPR2=0,SPPR1=0,SPPR0=0,??=0,SPR2=1,SPR1=0,SPR0=0 */
  setReg8(SPIBR, 0x04U);               /* Set the baud rate register */ 
  /* SPIC2: ??=0,??=0,??=0,MODFEN=0,BIDIROE=0,??=0,SPISWAI=0,SPC0=0 */
  setReg8(SPIC2, 0x00U);               /* Configure the SPI port - control register 2 */ 
  /* SPIC1: SPIE=0,SPE=0,SPTIE=0,MSTR=1,CPOL=0,CPHA=1,SSOE=0,LSBFE=0 */
  setReg8(SPIC1, 0x14U);               /* Configure the SPI port - control register 1 */ 
  SPIC1_SPE = 1U;                      /* Enable device */
}


/* END SPI. */

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
