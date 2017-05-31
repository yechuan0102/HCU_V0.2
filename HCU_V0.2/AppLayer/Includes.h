/*
 * Includes.h
 *
 *  Created on: Apr 29, 2017
 *      Author: YE_Chuan
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_

 /*
 **********************************************************************
 ** ===================================================================
 **                  System Type
 ** ===================================================================
 **********************************************************************
 */
#define HCUA (0)
#define HCUB (1)
#define HCU_Type HCUA

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
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
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

 /* User includes (#include below this line is not maintained by Processor Expert) */
#include "DataType.h"
#include "SysParameters.h"
#include "TaskSchedule.h"
#include "StateMachineManagement.h"


#endif /* INCLUDES_H_ */
