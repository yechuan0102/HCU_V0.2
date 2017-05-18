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
	
//	if (Task_ErrorDiagnosis);
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
		SYSTEM_AD_DATA.NTC_T[0] = Calc_ADData_NTC(737);
		SYSTEM_AD_DATA.NTC_T[1] = Calc_ADData_NTC(700);
		SYSTEM_AD_DATA.NTC_T[2] = Calc_ADData_NTC(665);
		SYSTEM_AD_DATA.NTC_T[3] = Calc_ADData_NTC(4028);
		SYSTEM_AD_DATA.NTC_T[4] = Calc_ADData_NTC(302);
		SYSTEM_AD_DATA.NTC_T[5] = Calc_ADData_NTC(RawData_NTC_T5);
		
		/*H2Con */
		SYSTEM_AD_DATA.H2Con[0] = Calc_ADData_H2Con(1000);
//		SYSTEM_AD_DATA.H2Con[1] = Calc_ADData_H2Con(RawData_H2Con1);
//		SYSTEM_AD_DATA.H2Con[2] = Calc_ADData_H2Con(1000);
//		SYSTEM_AD_DATA.H2Con[3] = Calc_ADData_H2Con(RawData_H2Con3);
//		SYSTEM_AD_DATA.H2Con[4] = Calc_ADData_H2Con(RawData_H2Con4);
//
		/*H2 Pressure */
		SYSTEM_AD_DATA.P_Tank	= Calc_ADData_P_H2Tank(3500);
		SYSTEM_AD_DATA.P_Mid	= Calc_ADData_P_H2Mid(2000);

	}
	else 
	{
		InnerFault_ADProcess = 1;
		if (ERR_OK == ADCH_Stop())	InnerFault_ADProcess = 0;
		else						InnerFault_ADProcess = 1;
		ADCH_Init();
	}
	
	if (ERR_OK == ADCH_Start())		InnerFault_ADProcess = 0;
	else							InnerFault_ADProcess = 1;
	/*clear Task_ADCHS Flag */
	Task_ADCHS = 0;
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
			Temp_Data = TData_Table[i] - ((Temp_RawData - TRawData_Table[i]) * 5 )/ (TRawData_Table[i - 1] - TRawData_Table[i]);
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
	Temp_Data = ((unsigned long)(Temp_RawData- H2ConRawData_Table[1])*(H2ConData_Table[0] - H2ConData_Table[1])) / (H2ConRawData_Table[0] - H2ConRawData_Table[1]) + H2ConData_Table[1];
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

/**************************************************************************************
Function:       //	AD_Lagrange
Called By:      //	Calc_ADData_NTC
				//	Calc_ADData_H2Con
				//	Calc_ADData_P_H2Tank
				//	Calc_ADData_P_H2Mid
Input:          //	const int x[]		RawData_Table
					const int y[],	Data_Table
					const int len,	Data_Table_len
					int xh		ADCHRawData
Return:         //	yh			ADCHData
Others:         //	NA
****************************************************************************************/
unsigned int AD_Lagrange(const unsigned int x[], const unsigned int y[], const int len, unsigned int xh)
{
	unsigned long yh;
	unsigned int y0,y1,x0,x1;
	int i;
	if (len == 2)
	{
		y0 = y[0];
		y1 = y[1];
		x0 = x[0];
		x1 = x[1];
		yh = (y0-y1);
		yh= xh*yh;
		yh = yh/(x0-x1)+y0;
	}
	else
	{
		for (i = 0; i < len; i++)
		{
			if (x[i] <= xh)	break;
		}
		if (i == 0)		i = 1;
		else if (i > (len - 1))	i = len - 1;
		if (i > 0 && i <= (len - 1))
		{
			y0 = y[i - 1];
			y1 = y[i];
			x0 = x[i - 1];
			x1 = x[i];			
			yh = xh*(y0-y1);
			yh	=y0-yh/(x1-x0);
		}			
	}
	
	//if (yh < 0)		yh = 0;
	return yh;

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
		if (TLE_ON_count >= 10)	//  only 1 channel will be open in 1s
		{
			TLECMD_Open1Channel();
			TLE_ON_count = 0;
		}
		TLE_OFF_count++;
		if (TLE_OFF_count >= 10)//  only 1 channel will be close in 1s
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
	systemp_Timer1++;
	CANTXD_MsgBufferUpdate();
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
	Msg_CAN_TXD[HCU2FCU_Msg1].data[0] = T_Tank1;
	Msg_CAN_TXD[HCU2FCU_Msg1].data[1] = T_Tank2;
	Msg_CAN_TXD[HCU2FCU_Msg1].data[2] = T_Tank3;
	Msg_CAN_TXD[HCU2FCU_Msg1].data[3] = T_Tank4;
	Msg_CAN_TXD[HCU2FCU_Msg1].data[4] = T_Tank5;
	Msg_CAN_TXD[HCU2FCU_Msg1].data[5] = 0x00;
	Msg_CAN_TXD[HCU2FCU_Msg1].data[6] = HCUStatus.Status;
	Msg_CAN_TXD[HCU2FCU_Msg1].data[7] = 0x00;//ERRCODE

	Msg_CAN_TXD[HCU2FCU_Msg2].data[0] = H2Con1;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[1] = H2Con2;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[2] = 0x00;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[3] = 0x00;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[4] = 0x00;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[5] = 0x00;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[6] = 0x00;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[7] = 0x00;
#endif // HCU_Type == HCUA
#if HCU_Type == HCUB
	Msg_CAN_TXD[HCU2FCU_Msg1].data[0] = T_Tank6;
	Msg_CAN_TXD[HCU2FCU_Msg1].data[1] = T_Tank7;
	Msg_CAN_TXD[HCU2FCU_Msg1].data[2] = (unsigned char)(P_H2Tank>>8);
	Msg_CAN_TXD[HCU2FCU_Msg1].data[3] = (unsigned char)(P_H2Tank);
	Msg_CAN_TXD[HCU2FCU_Msg1].data[4] = (unsigned char)(P_H2Mid >> 8);
	Msg_CAN_TXD[HCU2FCU_Msg1].data[5] = (unsigned char)(P_H2Mid);
	Msg_CAN_TXD[HCU2FCU_Msg1].data[6] = HCUStatus.Status;
	Msg_CAN_TXD[HCU2FCU_Msg1].data[7] = 0x00;//ERRCODE

	Msg_CAN_TXD[HCU2FCU_Msg2].data[0] = H2Con3;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[1] = H2Con4;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[2] = H2Con5;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[3] = H2Con6;
	Msg_CAN_TXD[HCU2FCU_Msg2].data[4] = H2Con7;
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
Called By:      // 
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void Task_ErrorDiagnosisProcess(void)
{
#if HCU_Type == HCUA
	/*if (SYSTEM_AD_DATA.NTC_T[1] == -1) 
	{
		SystemError.Bits.T_Tank1_SENSOR = 1; 
		if (Set_ErrGrade(ErrorGradeError)) 
			HCU_ErrorCode = ErrorCode_T_Tank1_SENSOR;
	}
	if (SYSTEM_AD_DATA.NTC_T[2] == -1) { SystemError.Bits.T_Tank2_SENSOR = 1; }
	if (SYSTEM_AD_DATA.NTC_T[3] == -1) { SystemError.Bits.T_Tank3_SENSOR = 1; }
	if (SYSTEM_AD_DATA.NTC_T[4] == -1) { SystemError.Bits.T_Tank4_SENSOR = 1; }
	if (SYSTEM_AD_DATA.NTC_T[5] == -1) { SystemError.Bits.T_Tank5_SENSOR = 1; }*/


	//if (SYSTEM_AD_DATA.NTC_T[1] >= );

#endif // HCU_Type == HCUA
#if HCU_Type == HCUB

#endif // HCU_Type == HCUB
}
int Set_ErrGrade(unsigned char ErrGrade)
{
	if (HCUStatus.MergedBits.ErrGrade < ErrGrade)
	{
		HCUStatus.MergedBits.ErrGrade = ErrGrade;
		return 1;
	}
	return 0;
}
