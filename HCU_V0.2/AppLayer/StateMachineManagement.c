/*
 * StateMachineManagement.c
 *
 *  Created on: Apr 29, 2017
 *      Author: YE_Chuan
 */

#include "Includes.h"


/**************************************************************************************
 Function:       // StateMachineManagement
 Called By:      // The main loop
 Input:          // void
 Return:         // void
 Others:         // NA
 ****************************************************************************************/
void StateMachineManagement(void)
{
	if (IsStatePowerUp)
	{
		SetStateReady;
	}
	else if (IsStateReady)
	{
		SetStateEnable;
	}
	else if (IsStateEnable)
	{

	}
	else if (IsStateError)
	{

	}
}
