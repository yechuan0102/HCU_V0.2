/*
 * TaskSchedule.c
 *
 *  Created on: Apr 27, 2017
 *      Author: YE_Chuan
 */
#include "Includes.h"

 /**************************************************************************************
 Function:       // TaskSchedule
 Called By:      // The main loop
 Input:          // void
 Return:         // void
 Others:         // NA
 ****************************************************************************************/
void TaskSchedule(void)
{
	if (Task_ADCHS)				Task_ADCHSProcess();
		
	if (Task_TLE6232)			Task_TLE6232Process();

	if (Task_CANTXD)			Task_CANTXD_Process();
	if (Task_FCUCMD)			Task_FCUCMD_Process();
	
	if (Task_ErrorDiagnosis)    Task_ErrorDiagnosisProcess();
}

/*
**********************************************************************
** ===================================================================
**              AD Functions in This Programme
** ===================================================================
**********************************************************************
*/

/**************************************************************************************
Function:       // TaskADCHSDataProcess
Called By:      // ADC onEnd Interrupt
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void Task_ADCHSProcess(void)
{
	if(ERR_OK == ADCH_GetValue((void*)ADCHRawData)) 
	{
		InnerFault_ADProcess = 0;
		/*Tank Temperature*/
		SYSTEM_AD_DATA.NTC_T[0] = Calc_ADData_NTC(RawData_NTC_T0);
		SYSTEM_AD_DATA.NTC_T[1] = Calc_ADData_NTC(RawData_NTC_T1);
		SYSTEM_AD_DATA.NTC_T[2] = Calc_ADData_NTC(RawData_NTC_T2);
		SYSTEM_AD_DATA.NTC_T[3] = Calc_ADData_NTC(RawData_NTC_T3);
		SYSTEM_AD_DATA.NTC_T[4] = Calc_ADData_NTC(RawData_NTC_T4);
		SYSTEM_AD_DATA.NTC_T[5] = Calc_ADData_NTC(RawData_NTC_T5);
		
		/*H2Con */
		SYSTEM_AD_DATA.H2Con[0] = Calc_ADData_H2Con(RawData_H2Con0);
		SYSTEM_AD_DATA.H2Con[1] = Calc_ADData_H2Con(RawData_H2Con1);
		SYSTEM_AD_DATA.H2Con[2] = Calc_ADData_H2Con(RawData_H2Con2);
		SYSTEM_AD_DATA.H2Con[3] = Calc_ADData_H2Con(RawData_H2Con3);
		SYSTEM_AD_DATA.H2Con[4] = Calc_ADData_H2Con(RawData_H2Con4);

		/*H2 Pressure */
		SYSTEM_AD_DATA.P_Tank	= Calc_ADData_P_H2Tank(RawData_P_H2Tank);
		SYSTEM_AD_DATA.P_Mid	= Calc_ADData_P_H2Mid(RawData_P_H2Mid);
		
		
	}
	else { InnerFault_ADProcess = 1; }
	
	/*** Clear Task Flag. DON'T MODIFY THIS CODE!!! ***/
	Task_ADCHS = 0;
	
	(void)ADCH_Measure(FALSE);
	
}

/**************************************************************************************
Function:       //	Calc_ADData_NTC
				//	Calc_ADData_H2Con
				//	Calc_ADData_P_H2Tank
				//	Calc_ADData_P_H2Mid
Called By:      //	Task_ADCHSProcess
Input:          //	ADCHRawData
Return:         //	SYSTEM_AD_DATA
Others:         //	NA
****************************************************************************************/
unsigned char Calc_ADData_NTC(unsigned int Temp_RawData)//-40~150 C   0-190   0.37-4.92V	
{
	unsigned int Temp_Data;
	unsigned char i;
	if (Temp_RawData > TDataRawLimitH) return 0xFF;	//sensor error
	if (Temp_RawData < TDataRawLimitL) return 0xFF;	//sensor error
	for (i = 1; i < TData_Table_Len; i++)
	{
		if ((TRawData_Table[i] <= Temp_RawData) && (Temp_RawData <= TRawData_Table[i - 1]))
		{
			Temp_Data = TData_Table[i] - ((Temp_RawData - TRawData_Table[i]) * 5) / (TRawData_Table[i - 1] - TRawData_Table[i]);
			break;
		}
	}
	

	return (unsigned char)Temp_Data;
}
unsigned char Calc_ADData_H2Con(unsigned int Temp_RawData)//0-20000ppm  0-200  0.5-4.5V  
{
	unsigned long Temp_Data;
	if (Temp_RawData > H2ConRawLimitH)	return 0xFF;	//sensor error
	else if (Temp_RawData < H2ConRawLimitL)	return 0xFF;	//sensor error
	
	if (Temp_RawData < H2ConRawData_Table[1]) return (unsigned char)H2ConData_Table[1];
	else if (Temp_RawData > H2ConRawData_Table[0]) return (unsigned char)H2ConData_Table[0];
	Temp_Data = ((unsigned long)(Temp_RawData - H2ConRawData_Table[1])*(H2ConData_Table[0] - H2ConData_Table[1])) / (H2ConRawData_Table[0] - H2ConRawData_Table[1]) + H2ConData_Table[1];
	return (unsigned char)Temp_Data;
}
unsigned int Calc_ADData_P_H2Tank(unsigned int Temp_RawData) //0-500barg  0-50000  1-5V
{
	unsigned long Temp_Data;
	if (Temp_RawData > P_H2TankDataRawLimitH)	return 0xFFFF;	//sensor error
	else if (Temp_RawData < P_H2TankDataRawLimitL)	return 0xFFFF;	//sensor error
	
	if (Temp_RawData < P_H2TankRawData_Table[1]) return P_H2TankData_Table[1];
	Temp_Data = ((unsigned long)(Temp_RawData - P_H2TankRawData_Table[1]) * (P_H2TankData_Table[0] - P_H2TankData_Table[1])) / (P_H2TankRawData_Table[0] - P_H2TankRawData_Table[1]) + P_H2TankData_Table[1];
	return (unsigned int)Temp_Data;
}
unsigned int Calc_ADData_P_H2Mid(unsigned int Temp_RawData) //0-20barg   0-2000  1-5V
{
	unsigned long Temp_Data;
	if (Temp_RawData > P_H2MidDataRawLimitH)	return 0xFFFF;	//sensor error
	else if (Temp_RawData < P_H2MidDataRawLimitL)	return 0xFFFF;	//sensor error
	
	if (Temp_RawData < P_H2MidRawData_Table[1]) 	return P_H2MidData_Table[1];
	Temp_Data = ((unsigned long)(Temp_RawData - P_H2MidRawData_Table[1]) * (P_H2MidData_Table[0] - P_H2MidData_Table[1])) / (P_H2MidRawData_Table[0] - P_H2MidRawData_Table[1]) + P_H2MidData_Table[1];
	return (unsigned int)Temp_Data;
}


/*
**********************************************************************
** ===================================================================
**              TLE Functions in This Programme
** ===================================================================
**********************************************************************
*/


/**************************************************************************************
Function:       // TLE_SPI_SendCMD
Called By:      // Task_TLE6232UpdateProcess
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
unsigned int TLE_SPI_SendCMD(unsigned char ControlByte, unsigned char DataByte ,unsigned int TLEType)
{
	volatile unsigned int timer;
	unsigned char tempResult = 0xFF;
	unsigned char tempDateH = 0;
	unsigned char tempDateL = 0;
	unsigned int	tempData = 0;
	unsigned char SPICOMFlag;
	unsigned char i=0;
	if (TLEType == TLE_1)
	{
		SPI_DriverINH_1_SetVal(); //Quit Reset State
		SPI_DriverSS_1_ClrVal();//Enable SPI Driver Chip
		for(i=0;i<10;i++);
	}
	else if (TLEType == TLE_2)
	{
		SPI_DriverINH_2_SetVal(); //Quit Reset State
		SPI_DriverSS_2_ClrVal();//Enable SPI Driver Chip
		for(i=0;i<10;i++);
	}
	else {}
	SPICOMFlag = 0x00;
	for (timer = 0; timer<SPIWaitStepLimit; timer++) { tempResult = SPI_SendChar(ControlByte); if (ERR_OK == tempResult) { SPICOMFlag |= 0X01; break; } }//Write the high byte   
	for (timer = 0; timer<SPIWaitStepLimit; timer++) { tempResult = SPI_RecvChar(&tempDateH); if (ERR_OK == tempResult) { SPICOMFlag |= 0X02; break; } }//Read SPI Driver status high byte
	for (timer = 0; timer<SPIWaitStepLimit; timer++) { tempResult = SPI_SendChar(DataByte); if (ERR_OK == tempResult) { SPICOMFlag |= 0X04; break; } }//Write the high byte   
	for (timer = 0; timer<SPIWaitStepLimit; timer++) { tempResult = SPI_RecvChar(&tempDateL); if (ERR_OK == tempResult) { SPICOMFlag |= 0X08; break; } }//Read SPI Driver status high byte
	if (TLEType == TLE_1)	
	{
		for(i=0;i<10;i++);
		SPI_DriverSS_1_SetVal(); //Disable SPI Driver Chip
			
	}
	else if (TLEType == TLE_2)	
	{
		for(i=0;i<10;i++);
		SPI_DriverSS_2_SetVal(); //Disable SPI Driver Chip
	}
	else{}
	if (SPICOMFlag & 0x0F == 0X0F)
	{
		InnerFault_SPIPorcess = 0;
		tempData = (((unsigned int)(tempDateH)) << 8) + ((unsigned int)(tempDateL));
	}
	else
	{
		InnerFault_SPIPorcess = 1;
		tempData = TLE_SEND_FAILED;
	}
	return tempData;
}


/**************************************************************************************
Function:       // TLECMD_Open1Channel
Called By:      // TLE6232CMDsetProcess
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void TLECMD_Open1Channel(void)
{
	if		(isTLE_OUT1_CMD_ON && !isTLE_OUT1_ON)		TLE_OUT1_ON;
	else if (isTLE_OUT2_CMD_ON && !isTLE_OUT2_ON)		TLE_OUT2_ON;
	else if (isTLE_OUT3_CMD_ON && !isTLE_OUT3_ON)		TLE_OUT3_ON;
	else if (isTLE_OUT4_CMD_ON && !isTLE_OUT4_ON)		TLE_OUT4_ON;
	else if (isTLE_OUT5_CMD_ON && !isTLE_OUT5_ON)		TLE_OUT5_ON;
	else if (isTLE_OUT6_CMD_ON && !isTLE_OUT6_ON)		TLE_OUT6_ON;
	else if (isTLE_OUT7_CMD_ON && !isTLE_OUT7_ON)		TLE_OUT7_ON;
	else if (isTLE_OUT8_CMD_ON && !isTLE_OUT8_ON)		TLE_OUT8_ON;
	else if (isTLE_OUT9_CMD_ON && !isTLE_OUT9_ON)		TLE_OUT9_ON;
	else if (isTLE_OUT10_CMD_ON && !isTLE_OUT10_ON)		TLE_OUT10_ON;
	else if (isTLE_OUT11_CMD_ON && !isTLE_OUT11_ON)		TLE_OUT11_ON;
	else if (isTLE_OUT12_CMD_ON && !isTLE_OUT12_ON)		TLE_OUT12_ON;
}
/**************************************************************************************
Function:       // TLECMD_Close1Channel
Called By:      // TLE6232CMDsetProcess
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void TLECMD_Close1Channel(void)
{
	if		(!isTLE_OUT1_CMD_ON && isTLE_OUT1_ON)		TLE_OUT1_OFF;
	else if (!isTLE_OUT2_CMD_ON && isTLE_OUT2_ON)		TLE_OUT2_OFF;
	else if (!isTLE_OUT3_CMD_ON && isTLE_OUT3_ON)		TLE_OUT3_OFF;
	else if (!isTLE_OUT4_CMD_ON && isTLE_OUT4_ON)		TLE_OUT4_OFF;
	else if (!isTLE_OUT5_CMD_ON && isTLE_OUT5_ON)		TLE_OUT5_OFF;
	else if (!isTLE_OUT6_CMD_ON && isTLE_OUT6_ON)		TLE_OUT6_OFF;
	else if (!isTLE_OUT7_CMD_ON && isTLE_OUT7_ON)		TLE_OUT7_OFF;
	else if (!isTLE_OUT8_CMD_ON && isTLE_OUT8_ON)		TLE_OUT8_OFF;
	else if (!isTLE_OUT9_CMD_ON && isTLE_OUT9_ON)		TLE_OUT9_OFF;
	else if (!isTLE_OUT10_CMD_ON && isTLE_OUT10_ON)		TLE_OUT10_OFF;
	else if (!isTLE_OUT11_CMD_ON && isTLE_OUT11_ON)		TLE_OUT11_OFF;
	else if (!isTLE_OUT12_CMD_ON && isTLE_OUT12_ON)		TLE_OUT12_OFF;
}

/**************************************************************************************
Function:       // TLE_CMDset
Called By:      // Task_TLE6232Process 
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void TLE_CMDset(void)
{
	static unsigned char TLE_ON_count = 0;
	static unsigned char TLE_OFF_count = 0;
	unsigned int i;
	if (IsStateEnable)
	{
		TLE_ON_count++;
		if (TLE_ON_count >= 5)	//  only 1 channel will be open in 1s
		{
			TLECMD_Open1Channel();
			TLE_ON_count = 0;
		}
		TLE_OFF_count++;
		if (TLE_OFF_count >= 5)//  only 1 channel will be close in 1s
		{
			TLECMD_Close1Channel();
			TLE_OFF_count = 0;
		}
	}
	if (IsStateError)
	{
		for (i = 0; i < 12; i++) { TLECMD_Close1Channel(); }
	}
}


unsigned char GetTLEFault1(void)
{
	return (SPI_DriverFault_1_GetVal());
}
unsigned char GetTLEFault2(void)
{
	return (SPI_DriverFault_2_GetVal()>>1);
}


/**************************************************************************************
Function:       // TLE_Update
Called By:      // Task_TLE6232Process 
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
/*****************************************************************************************************
** Here SPI controlled driver devices are updated by SPI communication,including write control word**
** and read channels and chip state; Because the flag bit in routine is not as same as chip logic **
** so flip it first before write to chips, also the hardware logic should be checked               **
*****************************************************************************************************/
void TLE_Update(void)
{
	unsigned int tempResult = 0x03ff;
	unsigned int tempREV;
	TLEFault1 = GetTLEFault1();
	TLEFault2 = GetTLEFault2();
	/*************************TLE1 CMD Send*************************/
	//Write MUX Register, Channel 1-6 Controled by SPI
	tempREV = TLE_SPI_SendCMD(TLE_WR_MUX, TLE_SET_MUX_SER, TLE_1);
	if (tempREV != (TLE_SEND_FAILED))	TLEErrFlag_1.TLEErrFlag = tempREV;
	//Write SCON Register, Send CMD
	tempREV = TLE_SPI_SendCMD(TLE_WR_SCON, TLECMD.DriverCMDBytes.DriverCMD1, TLE_1);
	if (tempREV != (TLE_SEND_FAILED))	TLEErrFlag_1.TLEErrFlag = tempREV;
	/*If there is any fault flag in [HCUA channel1(out2) channel4(out3)][HCUB channel1(out2) channel4(out3)]
	*Read and clear error flags by read diagnosis register
	*Using the 0x8000 */
	tempResult = TLEErrFlag_1.TLEErrFlag & TLEERRORMASK_1;
	if (tempResult != TLEERRORMASK_1)
	{
		tempREV = TLE_SPI_SendCMD(TLE_RD_DIAG, TLE_NULL, TLE_1);
		if (tempREV != (TLE_SEND_FAILED))	TLEErrFlag_1.TLEErrFlag = tempREV;
	}
	/*************************TLE2 CMD Send*************************/
	//Write MUX Register, Channel 1-6 Controled by SPI
	tempREV = TLE_SPI_SendCMD(TLE_WR_MUX, TLE_SET_MUX_SER, TLE_2);
	if (tempREV != (TLE_SEND_FAILED))	TLEErrFlag_2.TLEErrFlag = tempREV;
	//Write SCON Register, Send CMD
	tempREV = TLE_SPI_SendCMD(TLE_WR_SCON, TLECMD.DriverCMDBytes.DriverCMD2, TLE_2);
	if (tempREV != (TLE_SEND_FAILED))	TLEErrFlag_2.TLEErrFlag = tempREV;
	/*If there is any fault flag in [HCUA channel1(out7) channel2(out5) channel3(out4)]
	*Read and clear error flags by read diagnosis register
	*Using the 0x8000 */
	tempResult = TLEErrFlag_2.TLEErrFlag & TLEERRORMASK_2;
	if (tempResult != TLEERRORMASK_2)
	{
		tempREV = TLE_SPI_SendCMD(TLE_RD_DIAG, TLE_NULL, TLE_2);
		if (tempREV != (TLE_SEND_FAILED))	TLEErrFlag_2.TLEErrFlag = tempREV;
	}
}
/**************************************************************************************
Function:       // TLE_ErrorDIA
Called By:      // Task_TLE6232Process
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void TLE_ErrorDIA(void)
{
	TLEErrorOUT[0] = (TLEErrFlag_1.TLEErrBits.DIA6); // TLE1-OUT6	OUT1
	TLEErrorOUT[1] = (TLEErrFlag_1.TLEErrBits.DIA1); // TLE1-OUT1	OUT2
	TLEErrorOUT[2] = (TLEErrFlag_1.TLEErrBits.DIA4); // TLE1-OUT4	OUT3
	TLEErrorOUT[3] = (TLEErrFlag_2.TLEErrBits.DIA3); // TLE2-OUT3	OUT4
	TLEErrorOUT[4] = (TLEErrFlag_2.TLEErrBits.DIA2); // TLE2-OUT2	OUT5
	TLEErrorOUT[5] = (TLEErrFlag_2.TLEErrBits.DIA5); // TLE2-OUT5	OUT6
	TLEErrorOUT[6] = (TLEErrFlag_2.TLEErrBits.DIA1); // TLE2-OUT1	OUT7
	TLEErrorOUT[7] = (TLEErrFlag_1.TLEErrBits.DIA2); // TLE1-OUT2	OUT8
	TLEErrorOUT[8] = (TLEErrFlag_1.TLEErrBits.DIA5); // TLE1-OUT5	OUT9
	TLEErrorOUT[9] = (TLEErrFlag_1.TLEErrBits.DIA3); // TLE1-OUT3	OUT10
	TLEErrorOUT[10] = (TLEErrFlag_2.TLEErrBits.DIA4); // TLE2-OUT4	OUT11
	TLEErrorOUT[11] = (TLEErrFlag_2.TLEErrBits.DIA6); // TLE2-OUT6 	OUT12
}
/**************************************************************************************
Function:       // Task_TLE6232Process
Called By:      // 100ms Interrupt
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void Task_TLE6232Process(void)
{
	TLE_CMDset();
	TLE_Update();
	TLE_ErrorDIA();
	/*** Clear Task Flag. DON'T MODIFY THIS CODE!!! ***/
	Task_TLE6232 = 0;
}

/*
**********************************************************************
** ===================================================================
**              CAN Functions in This Programme
** ===================================================================
**********************************************************************
*/

/**************************************************************************************
Function:       // Task_CANTXD_Process
Called By:      // CAN_Send_Delay
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void Task_CANTXD_Process(void)
{
	CANTXD_MsgBufferUpdate();
	ErrorTimer_CAN = 0;
	EnableCANTXD;
	/*** Clear Task Flag. DON'T MODIFY THIS CODE!!! ***/
	Task_CANTXD = 0;
}
/**************************************************************************************
Function:       // CANTXD_MsgBufferUpdate
Called By:      // Task_CANTXD_Process
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void CANTXD_MsgBufferUpdate(void)
{
	#if HCU_Type == HCUA
		Msg_CAN_TXD[HCU2FCU_Msg1].data[0] = PhysData_T_Tank1;
		Msg_CAN_TXD[HCU2FCU_Msg1].data[1] = PhysData_T_Tank2;
		Msg_CAN_TXD[HCU2FCU_Msg1].data[2] = PhysData_T_Tank3;
		Msg_CAN_TXD[HCU2FCU_Msg1].data[3] = PhysData_T_Tank4;
		Msg_CAN_TXD[HCU2FCU_Msg1].data[4] = PhysData_T_Tank5;
		Msg_CAN_TXD[HCU2FCU_Msg1].data[5] = 0x00;
		Msg_CAN_TXD[HCU2FCU_Msg1].data[6] = HCUStatus.Status;
		Msg_CAN_TXD[HCU2FCU_Msg1].data[7] = 0x00;//ERRCODE
	
		Msg_CAN_TXD[HCU2FCU_Msg2].data[0] = PhysData_H2Con1;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[1] = PhysData_H2Con2;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[2] = 0x00;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[3] = 0x00;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[4] = 0x00;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[5] = 0x00;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[6] = 0x00;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[7] = 0x00;
	#endif // HCU_Type == HCUA
	#if HCU_Type == HCUB
		Msg_CAN_TXD[HCU2FCU_Msg1].data[0] = PhysData_T_Tank6;
		Msg_CAN_TXD[HCU2FCU_Msg1].data[1] = PhysData_T_Tank7;
		Msg_CAN_TXD[HCU2FCU_Msg1].data[2] = (unsigned char)(PhysData_P_H2Tank);
		Msg_CAN_TXD[HCU2FCU_Msg1].data[3] = (unsigned char)(PhysData_P_H2Tank >>8);
		Msg_CAN_TXD[HCU2FCU_Msg1].data[4] = (unsigned char)(PhysData_P_H2Mid);
		Msg_CAN_TXD[HCU2FCU_Msg1].data[5] = (unsigned char)(PhysData_P_H2Mid >> 8);
		Msg_CAN_TXD[HCU2FCU_Msg1].data[6] = HCUStatus.Status;
		Msg_CAN_TXD[HCU2FCU_Msg1].data[7] = 0x00;//ERRCODE
	
		Msg_CAN_TXD[HCU2FCU_Msg2].data[0] = PhysData_H2Con3;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[1] = PhysData_H2Con4;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[2] = PhysData_H2Con5;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[3] = PhysData_H2Con6;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[4] = PhysData_H2Con7;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[5] = 0x00;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[6] = 0x00;
		Msg_CAN_TXD[HCU2FCU_Msg2].data[7] = 0x00;
	#endif // HCU_Type == HCUB
}

/**************************************************************************************
Function:       // CANDownLoad
Called By:      // CAN REV ISR
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void CANDownLoad(void)
{
	static CAN_Message tempCANMSG;
	unsigned char TempIndex, DataIndex;

	if (ERR_OK == CAN_ReadFrame((dword *)(&tempCANMSG.ID.ID), (byte *)(&tempCANMSG.FrameType), (byte *)(&tempCANMSG.FrameFormat), (byte *)(&tempCANMSG.length), (byte *)(&tempCANMSG.data)))
	{
		for (TempIndex = 0; TempIndex<CAN_RXD_NUM; TempIndex++)
		{
			if ((Msg_CAN_RXD[TempIndex].ID.ID == tempCANMSG.ID.ID))
			{
				Msg_CAN_RXD[TempIndex].FrameFormat = tempCANMSG.FrameFormat;
				Msg_CAN_RXD[TempIndex].FrameType = tempCANMSG.FrameType;
				Msg_CAN_RXD[TempIndex].length = tempCANMSG.length;
				for (DataIndex = 0; DataIndex<tempCANMSG.length; DataIndex++)
				{
					Msg_CAN_RXD[TempIndex].data[DataIndex] = tempCANMSG.data[DataIndex];
				}
				if (TempIndex == FCU2HCU_Msg) 
				{
					(void)TI_1ms_Enable();
					Task_FCUCMD = 1;
				}
			}
		}
	}
}
/**************************************************************************************
Function:       // Task_FCUCMD_Process
Called By:      // CAN REV ISR
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
/*FOR CAN Message		H = ON  or L = OFF*/
/*For TLE6232 SCON_REG	H = OFF or L = ON*/
void Task_FCUCMD_Process(void)
{
	Data_Bits8 TLECtrl;
	TLECtrl.Data = Msg_CAN_RXD[FCU2HCU_Msg].data[0];
	#if HCU_Type == HCUA
		TLECMDTarget.DriverCMDBits.OUT2 = ~TLECtrl.Bits.BIT0;	//Tank1
		TLECMDTarget.DriverCMDBits.OUT3 = ~TLECtrl.Bits.BIT1;	//Tank2
		TLECMDTarget.DriverCMDBits.OUT4 = ~TLECtrl.Bits.BIT2;	//Tank3
		TLECMDTarget.DriverCMDBits.OUT5 = ~TLECtrl.Bits.BIT3;	//Tank4
		TLECMDTarget.DriverCMDBits.OUT7 = ~TLECtrl.Bits.BIT4;	//Tank5
	#endif // HCU_Type == HCUA
	#if HCU_Type == HCUB
		TLECMDTarget.DriverCMDBits.OUT2 = ~TLECtrl.Bits.BIT0;	//Tank6
		TLECMDTarget.DriverCMDBits.OUT3 = ~TLECtrl.Bits.BIT1;	//Tank7
	#endif // HCU_Type == HCUB

	/*** Clear Task Flag. DON'T MODIFY THIS CODE!!! ***/
	Task_FCUCMD = 0;
}

/**************************************************************************************
Function:       // Task_ErrorDiagnosisProcess
Called By:      // 20ms Interrupt
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void Task_ErrorDiagnosisProcess(void)
{
	SetErrorFlag();
	ErrorReport();

	

	/*** Clear Task Flag. DON'T MODIFY THIS CODE!!! ***/
	Task_ErrorDiagnosis = 0;
}

/**************************************************************************************
Function:       // SetErrorFlag
Called By:      // Task_ErrorDiagnosisProcess
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void SetErrorFlag(void)
{
	unsigned char i;
	static volatile unsigned int ErrorTimer_H2Con[5];
	static volatile unsigned int ErrorTimer_P_H2Mid_H;
	static volatile unsigned int ErrorTimer_P_H2Mid_L;
	for (i = 0; i < 5; i++)	{	ErrorTimer_H2Con[i] = 0;	}
	ErrorTimer_P_H2Mid_H = 0;
	ErrorTimer_P_H2Mid_L = 0;
	//6 Channel NTC
	for (i = 0; i < 6; i++)	
	{
		if (SYSTEM_AD_DATA.NTC_T[i] == 0xFF)
		{
			SysErrFlag.NTC[i].Detail.ErrorType = ERRTypeNTC_Sensor;
			SysErrFlag.NTC[i].Detail.ErrorGrade = ErrorGradeError;
		}
		else if (SYSTEM_AD_DATA.NTC_T[i] >= NTC_T_LimitH)
		{
			SysErrFlag.NTC[i].Detail.ErrorType = ERRTypeNTC_OTError;
			SysErrFlag.NTC[i].Detail.ErrorGrade = ErrorGradeError;
		}
		else if (SYSTEM_AD_DATA.NTC_T[i] >= NTC_T_LimitL )
		{
			SysErrFlag.NTC[i].Detail.ErrorType = ERRTypeNTC_OTAlarm;
			SysErrFlag.NTC[i].Detail.ErrorGrade = ErrorGradeAlarm;
		}
		else if ((SYSTEM_AD_DATA.NTC_T[i] < NTC_T_Rev))
		{
			SysErrFlag.NTC[i].Detail.ErrorType = ERRTypeOK;
			SysErrFlag.NTC[i].Detail.ErrorGrade = ErrorGradeOK;
		}
		else {}
	}

#if HCU_Type==HCUA
	//2 Channal H2Con for HCUA
	for (i = 0; i < 2; i++)  //Storage Cabin H2Con1 H2Con2
	{
		if (SYSTEM_AD_DATA.H2Con[i] == 0xFF)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Sensor;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeEmergency;
		}
		else if (SYSTEM_AD_DATA.H2Con[i] >= H2Con_StoLimitH)
		{
			ErrorTimer_H2Con[i]++;
			if (ErrorTimer_H2Con[i] >= Error_2s)
			{
				SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Emergency;
				SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeEmergency;
			}
		}
		else if (SYSTEM_AD_DATA.H2Con[i] >= H2Con_StoLimitL)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Alarm;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeAlarm;
		}
		else if (SYSTEM_AD_DATA.H2Con[i] < H2Con_StoLimitRev)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeOK;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeOK;
		}
		else {
			ErrorTimer_H2Con[i] = 0;
		}
	}
#endif // HCU_Type==HCUA


#if HCU_Type==HCUB
	//5 Channal H2Con for HCUB
	for (i = 0; i < 2; i++)  //Storage Cabin  H2Con1 H2Con2
	{
		if (SYSTEM_AD_DATA.H2Con[i] == 0xFF)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Sensor;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeEmergency;
		}
		else if (SYSTEM_AD_DATA.H2Con[i] >= H2Con_StoLimitH)
		{
			ErrorTimer_H2Con[i]++;
			if (ErrorTimer_H2Con[i] >= Error_2s)
			{
				SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Emergency;
				SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeEmergency;
			}
		}
		else if (SYSTEM_AD_DATA.H2Con[i] >= H2Con_StoLimitL)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Alarm;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeAlarm;
		}
		else if (SYSTEM_AD_DATA.H2Con[i] < H2Con_StoLimitRev)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeOK;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeOK;
		}
		else 
		{
			ErrorTimer_H2Con[i] = 0;
		}
	}
	for (i = 2; i < 4; i++) //Engine Cabin  H2Con3 H2Con4
	{
		if (SYSTEM_AD_DATA.H2Con[i] == 0xFF)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Sensor;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeEmergency;
		}
		else if (SYSTEM_AD_DATA.H2Con[i] >= H2Con_EngineLimitH)
		{
			ErrorTimer_H2Con[i]++;
			if (ErrorTimer_H2Con[i] >= Error_2s)
			{
				SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Emergency;
				SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeEmergency;
			}
		}
		else if (SYSTEM_AD_DATA.H2Con[i] >= H2Con_EngineLimitL )
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Alarm;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeAlarm;
		}
		else if (SYSTEM_AD_DATA.H2Con[i] < H2Con_EngineRev)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeOK;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeOK;
		}
		else {
			ErrorTimer_H2Con[i] = 0;
		}
	}
	for (i = 4; i < 5; i++) //Passenger Cabin H2Con5
	{
		if (SYSTEM_AD_DATA.H2Con[i] == 0xFF)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Sensor;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeEmergency;
		}
		else if (SYSTEM_AD_DATA.H2Con[i] >= H2Con_CabinLimitH)
		{
			ErrorTimer_H2Con[i]++;
			if (ErrorTimer_H2Con[i] >= Error_2s)
			{
				SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Emergency;
				SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeEmergency;
			}
		}
		else if (SYSTEM_AD_DATA.H2Con[i] >= H2Con_CabinLimitL)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeH2Con_Alarm;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeAlarm;
		}
		else if (SYSTEM_AD_DATA.H2Con[i] < H2Con_CabinRev)
		{
			ErrorTimer_H2Con[i] = 0;
			SysErrFlag.H2Con[i].Detail.ErrorType = ERRTypeOK;
			SysErrFlag.H2Con[i].Detail.ErrorGrade = ErrorGradeOK;
		}
		else {
			ErrorTimer_H2Con[i] = 0;
		}
	}
#endif // HCU_Type==HCUB

	
	// P_H2Tank
	if (SYSTEM_AD_DATA.P_Tank == 0xFFFF)
	{
		SysErrFlag.P_H2Tank.Detail.ErrorType = ERRTypeP_H2Tank_Sensor;
		SysErrFlag.P_H2Tank.Detail.ErrorGrade = ErrorGradeEmergency;
	}
	else if (SYSTEM_AD_DATA.P_Tank >= P_H2Tank_Limit)
	{
		SysErrFlag.P_H2Tank.Detail.ErrorType = ERRTypeP_H2Tank_H;
		SysErrFlag.P_H2Tank.Detail.ErrorGrade = ErrorGradeError;
	}
	else
	{
		SysErrFlag.P_H2Tank.Detail.ErrorType = ERRTypeOK;
		SysErrFlag.P_H2Tank.Detail.ErrorGrade = ErrorGradeOK;
	}
	//P_H2Mid
	if (SYSTEM_AD_DATA.P_Mid == 0xFFFF)
	{
		ErrorTimer_P_H2Mid_H = 0;
		ErrorTimer_P_H2Mid_L = 0;
		SysErrFlag.P_H2Mid.Detail.ErrorType = ERRTypeP_H2Mid_Sensor;
		SysErrFlag.P_H2Mid.Detail.ErrorGrade = ErrorGradeError;
	}
	else if (SYSTEM_AD_DATA.P_Mid >= P_H2Mid_LimitH)
	{
		ErrorTimer_P_H2Mid_H++;
		ErrorTimer_P_H2Mid_L = 0;
		if (ErrorTimer_P_H2Mid_H >= Error_5s) 
		{
			SysErrFlag.P_H2Mid.Detail.ErrorType = ERRTypeP_H2Mid_H;
			SysErrFlag.P_H2Mid.Detail.ErrorGrade = ErrorGradeError;
		}
	}
	else 
	{
		ErrorTimer_P_H2Mid_H = 0;
		ErrorTimer_P_H2Mid_L = 0;
		SysErrFlag.P_H2Mid.Detail.ErrorType = ERRTypeOK;
		SysErrFlag.P_H2Mid.Detail.ErrorGrade = ErrorGradeOK;
	}


	//12 Channel TLE OUT 

	for (i = 0; i < 12; i++)
	{
		if (TLEErrorOUT[i] == TLEErrorOK)
		{
			SysErrFlag.TLEOUT[i].Detail.ErrorType = ERRTypeOK;
			SysErrFlag.TLEOUT[i].Detail.ErrorGrade = ErrorGradeOK;
		}
		else if (TLEErrorOUT[i] == TLEErrorOT)
		{
			SysErrFlag.TLEOUT[i].Detail.ErrorType = ERRTypeTLEOT;
			SysErrFlag.TLEOUT[i].Detail.ErrorGrade = ErrorGradeAlarm;
		}
		else if (TLEErrorOUT[i] == TLEErrorOL)
		{
			SysErrFlag.TLEOUT[i].Detail.ErrorType = ERRTypeTLEOL;
			SysErrFlag.TLEOUT[i].Detail.ErrorGrade = ErrorGradeAlarm;
		}
		else if (TLEErrorOUT[i] == TLEErrorSCG)
		{
			SysErrFlag.TLEOUT[i].Detail.ErrorType = ERRTypeTLESCG;
			SysErrFlag.TLEOUT[i].Detail.ErrorGrade = ErrorGradeError;
		}
	}
	/*CAN lost*/
	if (ErrorTimer_CAN != 0xff)
	{
		ErrorTimer_CAN++;
		if (ErrorTimer_CAN >= Error_2s) //2s
		{
			SysErrFlag.CAN.Detail.ErrorType = ERRTypeCAN;
			SysErrFlag.CAN.Detail.ErrorGrade = ErrorGradeError;
		}
	}
}


/**************************************************************************************
Function:       // Set_ErrCode
Called By:      // ErrorReport
Input:          // ErrCode
Return:         // NA
Others:         // NA
****************************************************************************************/
void Set_ErrCode(unsigned char ErrCode)
{
	if (HCU_ErrorCode_Current.ErrorCode < ErrCode) HCU_ErrorCode_Current.ErrorCode = ErrCode;
}

/**************************************************************************************
Function:       // ErrorReport
Called By:      // Task_ErrorDiagnosisProcess
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void ErrorReport(void)
{
	unsigned char temp_ErrorCount;
	//reset ErrorCode ErrorGrade
	Set_ErrCode(ErrorCodeOK);
#if HCU_Type == HCUA
	/*5 Channel NTC*/
	// >75C Alarm
	temp_ErrorCount = 0;
	if (ErrorFlag_NTC1.Detail.ErrorType == ERRTypeNTC_OTAlarm) { temp_ErrorCount++;	Set_ErrCode(ErrorCode_T_Tank_OTAlarm); }
	if (ErrorFlag_NTC2.Detail.ErrorType == ERRTypeNTC_OTAlarm) { temp_ErrorCount++;	Set_ErrCode(ErrorCode_T_Tank_OTAlarm); }
	if (ErrorFlag_NTC3.Detail.ErrorType == ERRTypeNTC_OTAlarm) { temp_ErrorCount++;	Set_ErrCode(ErrorCode_T_Tank_OTAlarm); }
	if (ErrorFlag_NTC4.Detail.ErrorType == ERRTypeNTC_OTAlarm) { temp_ErrorCount++;	Set_ErrCode(ErrorCode_T_Tank_OTAlarm); }
	if (ErrorFlag_NTC5.Detail.ErrorType == ERRTypeNTC_OTAlarm) { temp_ErrorCount++;	Set_ErrCode(ErrorCode_T_Tank_OTAlarm); }
	if (temp_ErrorCount == 5) { Set_ErrCode(ErrorCode_T_Tank_OTError); }
	//>85C Error
	if (ErrorFlag_NTC1.Detail.ErrorType == ERRTypeNTC_OTError) { Set_ErrCode(ErrorCode_T_Tank_OTError); }
	if (ErrorFlag_NTC2.Detail.ErrorType == ERRTypeNTC_OTError) { Set_ErrCode(ErrorCode_T_Tank_OTError); }
	if (ErrorFlag_NTC3.Detail.ErrorType == ERRTypeNTC_OTError) { Set_ErrCode(ErrorCode_T_Tank_OTError); }
	if (ErrorFlag_NTC4.Detail.ErrorType == ERRTypeNTC_OTError) { Set_ErrCode(ErrorCode_T_Tank_OTError); }
	if (ErrorFlag_NTC5.Detail.ErrorType == ERRTypeNTC_OTError) { Set_ErrCode(ErrorCode_T_Tank_OTError); }
	//sensor Error
	if (ErrorFlag_NTC1.Detail.ErrorType == ERRTypeNTC_Sensor) { Set_ErrCode(ErrorCode_T_Tank_SENSOR); }
	if (ErrorFlag_NTC2.Detail.ErrorType == ERRTypeNTC_Sensor) { Set_ErrCode(ErrorCode_T_Tank_SENSOR); }
	if (ErrorFlag_NTC3.Detail.ErrorType == ERRTypeNTC_Sensor) { Set_ErrCode(ErrorCode_T_Tank_SENSOR); }
	if (ErrorFlag_NTC4.Detail.ErrorType == ERRTypeNTC_Sensor) { Set_ErrCode(ErrorCode_T_Tank_SENSOR); }
	if (ErrorFlag_NTC5.Detail.ErrorType == ERRTypeNTC_Sensor) { Set_ErrCode(ErrorCode_T_Tank_SENSOR); }

	/*2Channel H2Con*/
	// Alarm
	if (ErrorFlag_H2Con1.Detail.ErrorType == ERRTypeH2Con_Alarm) { Set_ErrCode(ErrorCode_StoH2Con_Alarm); }
	if (ErrorFlag_H2Con2.Detail.ErrorType == ERRTypeH2Con_Alarm) { Set_ErrCode(ErrorCode_StoH2Con_Alarm); }
	//Emergency
	if (ErrorFlag_H2Con1.Detail.ErrorType == ERRTypeH2Con_Emergency) { Set_ErrCode(ErrorCode_StoH2Con_Emergency); }
	if (ErrorFlag_H2Con2.Detail.ErrorType == ERRTypeH2Con_Emergency) { Set_ErrCode(ErrorCode_StoH2Con_Emergency); }
	//Sensor
	if (ErrorFlag_H2Con1.Detail.ErrorType == ERRTypeH2Con_Sensor) { Set_ErrCode(ErrorCode_StoH2Con_Sensor); }
	if (ErrorFlag_H2Con2.Detail.ErrorType == ERRTypeH2Con_Sensor) { Set_ErrCode(ErrorCode_StoH2Con_Sensor); }

	/*5 Channel TLE OUT  OUT2 OUT3 OUT4 OUT5 OUT7*/
	//OT OL SCB Alarm
	temp_ErrorCount = 0;
	if (ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLEOT || ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLEOL) { temp_ErrorCount++; Set_ErrCode(ErrorCode_TLEOUT_OT_Part); }
	if (ErrorFlag_TLEOUT3.Detail.ErrorType == ERRTypeTLEOT || ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLEOL) { temp_ErrorCount++; Set_ErrCode(ErrorCode_TLEOUT_OT_Part); }
	if (ErrorFlag_TLEOUT4.Detail.ErrorType == ERRTypeTLEOT || ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLEOL) { temp_ErrorCount++; Set_ErrCode(ErrorCode_TLEOUT_OT_Part); }
	if (ErrorFlag_TLEOUT5.Detail.ErrorType == ERRTypeTLEOT || ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLEOL) { temp_ErrorCount++; Set_ErrCode(ErrorCode_TLEOUT_OT_Part); }
	if (ErrorFlag_TLEOUT7.Detail.ErrorType == ERRTypeTLEOT || ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLEOL) { temp_ErrorCount++; Set_ErrCode(ErrorCode_TLEOUT_OT_Part); }
	if (temp_ErrorCount == 5) { Set_ErrCode(ErrorCode_TLEOUT_OT_All); }
	//SCG
	if (ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLESCG) { Set_ErrCode(ErrorCode_TLEOUT_SCG); }
	if (ErrorFlag_TLEOUT3.Detail.ErrorType == ERRTypeTLESCG) { Set_ErrCode(ErrorCode_TLEOUT_SCG); }
	if (ErrorFlag_TLEOUT4.Detail.ErrorType == ERRTypeTLESCG) { Set_ErrCode(ErrorCode_TLEOUT_SCG); }
	if (ErrorFlag_TLEOUT5.Detail.ErrorType == ERRTypeTLESCG) { Set_ErrCode(ErrorCode_TLEOUT_SCG); }
	if (ErrorFlag_TLEOUT7.Detail.ErrorType == ERRTypeTLESCG) { Set_ErrCode(ErrorCode_TLEOUT_SCG); }

	/*CAN */
	if (ErrorFlag_CAN.Detail.ErrorType == ERRTypeCAN) { Set_ErrCode(ErrorCode_CAN); }
#endif // HCU_Type == HCUA
#if HCU_Type == HCUB
	/*2 Channel NTC*/
	// >75C Alarm
	temp_ErrorCount = 0;
	if (ErrorFlag_NTC1.Detail.ErrorType == ERRTypeNTC_OTAlarm) { temp_ErrorCount++;	Set_ErrCode(ErrorCode_T_Tank_OTAlarm); }
	if (ErrorFlag_NTC2.Detail.ErrorType == ERRTypeNTC_OTAlarm) { temp_ErrorCount++;	Set_ErrCode(ErrorCode_T_Tank_OTAlarm); }
	if (temp_ErrorCount == 2) { Set_ErrCode(ErrorCode_T_Tank_OTError); }
	//>85C Error
	if (ErrorFlag_NTC1.Detail.ErrorType == ERRTypeNTC_OTError) { Set_ErrCode(ErrorCode_T_Tank_OTError); }
	if (ErrorFlag_NTC2.Detail.ErrorType == ERRTypeNTC_OTError) { Set_ErrCode(ErrorCode_T_Tank_OTError); }
	//sensor Error
	if (ErrorFlag_NTC1.Detail.ErrorType == ERRTypeNTC_Sensor) { Set_ErrCode(ErrorCode_T_Tank_SENSOR); }
	if (ErrorFlag_NTC2.Detail.ErrorType == ERRTypeNTC_Sensor) { Set_ErrCode(ErrorCode_T_Tank_SENSOR); }
	
	/*5 Channel H2Con*/
	/****Storage Cabin  H2Con1 H2Con2*****/
	// Alarm
	if (ErrorFlag_H2Con1.Detail.ErrorType == ERRTypeH2Con_Alarm) { Set_ErrCode(ErrorCode_StoH2Con_Alarm); }
	if (ErrorFlag_H2Con2.Detail.ErrorType == ERRTypeH2Con_Alarm) { Set_ErrCode(ErrorCode_StoH2Con_Alarm); }
	//Emergency
	if (ErrorFlag_H2Con1.Detail.ErrorType == ERRTypeH2Con_Emergency) { Set_ErrCode(ErrorCode_StoH2Con_Emergency); }
	if (ErrorFlag_H2Con2.Detail.ErrorType == ERRTypeH2Con_Emergency) { Set_ErrCode(ErrorCode_StoH2Con_Emergency); }
	//Sensor
	if (ErrorFlag_H2Con1.Detail.ErrorType == ERRTypeH2Con_Sensor) { Set_ErrCode(ErrorCode_StoH2Con_Sensor); }
	if (ErrorFlag_H2Con2.Detail.ErrorType == ERRTypeH2Con_Sensor) { Set_ErrCode(ErrorCode_StoH2Con_Sensor); }
	/****Engine Cabin  H2Con3 H2Con4*****/
	// Alarm
	if (ErrorFlag_H2Con3.Detail.ErrorType == ERRTypeH2Con_Alarm) { Set_ErrCode(ErrorCode_EngineH2Con_Alarm); }
	if (ErrorFlag_H2Con4.Detail.ErrorType == ERRTypeH2Con_Alarm) { Set_ErrCode(ErrorCode_EngineH2Con_Alarm); }
	//Emergency
	if (ErrorFlag_H2Con3.Detail.ErrorType == ERRTypeH2Con_Emergency) { Set_ErrCode(ErrorCode_EngineH2Con_Emergency); }
	if (ErrorFlag_H2Con4.Detail.ErrorType == ERRTypeH2Con_Emergency) { Set_ErrCode(ErrorCode_EngineH2Con_Emergency); }
	//Sensor
	if (ErrorFlag_H2Con3.Detail.ErrorType == ERRTypeH2Con_Sensor) { Set_ErrCode(ErrorCode_EngineH2Con_Sensor); }
	if (ErrorFlag_H2Con4.Detail.ErrorType == ERRTypeH2Con_Sensor) { Set_ErrCode(ErrorCode_EngineH2Con_Sensor); }
	/****Engine Cabin  H2Con5 *****/
	// Alarm
	if (ErrorFlag_H2Con5.Detail.ErrorType == ERRTypeH2Con_Alarm) { Set_ErrCode(ErrorCode_CabinH2Con_Alarm); }
	//Emergency
	if (ErrorFlag_H2Con5.Detail.ErrorType == ERRTypeH2Con_Emergency) { Set_ErrCode(ErrorCode_CabinH2Con_Emergency); }
	//Sensor
	if (ErrorFlag_H2Con5.Detail.ErrorType == ERRTypeH2Con_Sensor) { Set_ErrCode(ErrorCode_CabinH2Con_Sensor); }

	/*2 Channel TLE OUT  OUT2 OUT3 OUT4 OUT5 OUT7*/
	//OT OL SCB Alarm
	temp_ErrorCount = 0;
	if (ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLEOT || ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLEOL) { temp_ErrorCount++; Set_ErrCode(ErrorCode_TLEOUT_OT_Part); }
	if (ErrorFlag_TLEOUT3.Detail.ErrorType == ERRTypeTLEOT || ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLEOL) { temp_ErrorCount++; Set_ErrCode(ErrorCode_TLEOUT_OT_Part); }
	if (temp_ErrorCount == 2) { Set_ErrCode(ErrorCode_TLEOUT_OT_All); }
	//SCG
	if (ErrorFlag_TLEOUT2.Detail.ErrorType == ERRTypeTLESCG) { Set_ErrCode(ErrorCode_TLEOUT_SCG); }
	if (ErrorFlag_TLEOUT3.Detail.ErrorType == ERRTypeTLESCG) { Set_ErrCode(ErrorCode_TLEOUT_SCG); }

	/* CAN */
	if (ErrorFlag_CAN.Detail.ErrorType == ERRTypeCAN) { Set_ErrCode(ErrorCode_CAN); }
#endif // HCU_Type == HCUB

	HCU_ErrorGrade_Current = HCU_ErrorCode_Current.MergedBits.ErrorGrade;
	if ((HCUStatus.MergedBits.ErrGrade == ErrorGradeEmergency) || (HCUStatus.MergedBits.ErrGrade == ErrorGradeError))
	{
		if (HCU_ErrorCode_Current.ErrorCode >= HCU_ErrorCode.ErrorCode)
		{
			HCU_ErrorCode.ErrorCode = HCU_ErrorCode_Current.ErrorCode;
			HCUStatus.MergedBits.ErrGrade = HCU_ErrorGrade_Current;
		}
	}
	else
	{
		HCU_ErrorCode.ErrorCode = HCU_ErrorCode_Current.ErrorCode;
		HCUStatus.MergedBits.ErrGrade = HCU_ErrorGrade_Current;
	}
}
