/*
 * SysParameters.c
 *
 *  Created on: Apr 27, 2017
 *      Author: YE_Chuan
 */

#include "Includes.h"

/*System Flag*/
volatile WordFlags TaskFlags;
volatile unsigned char Timer_100ms = 0;
volatile unsigned char Timer_CAN;

/*AD Data*/
volatile unsigned int  ADCHRawData[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
volatile AD_Date SYSTEM_AD_DATA;

const unsigned int TRawData_Table[TData_Table_Len] =
{
	4028,	4007,	3979,	3944,	3902,	3849,	3787,	3712,	
	3625,	3524,	3410,	3282,	3141,	2989,	2828,	2660,
	2487,	2312,	2139,	1969,	1805,	1647,	1499,	1360,	
	1232,	1114,	1005,	907	,	818	,	738	,	666	,	601	,	
	542	,	490	,	443	,	401	,	365	,	332	,	302
};
const unsigned int TData_Table[TData_Table_Len] =
{
	0,		5,		10,		15,		20,		25,		30,		35,		
	40,		45,		50,		55,		60,		65,		70,		75,		
	80,		85,		90,		95,		100,	105,	110,	115,	
	120,	125,	130,	135,	140,	145,	150,	155,	
	160,	165,	170,	175,	180,	185,	190
};

const unsigned int H2ConRawData_Table[H2ConData_Table_Len] =
{	3686,	410};
const unsigned int H2ConData_Table[H2ConData_Table_Len] =
{	100,	0};

const unsigned int P_H2TankRawData_Table[P_H2TankData_Table_Len] =
{	4096,	819};
const unsigned int  P_H2TankData_Table[P_H2TankData_Table_Len] =
{	50000,	0};

const unsigned int P_H2MidRawData_Table[P_H2MidData_Table_Len] =
{	4096,	819};
const unsigned int  P_H2MidData_Table[P_H2MidData_Table_Len] =
{	2000,	0};



volatile StatusDef HCUStatus;
volatile unsigned char HCU_ErrorGrade_Current = ErrorGradeOK;
volatile HCU_ERROR_CODE HCU_ErrorCode;
volatile HCU_ERROR_CODE HCU_ErrorCode_Current;

volatile SYSTEM_ERROR_FLAG SysErrFlag;
volatile unsigned char ErrorTimer_CAN;

volatile WordFlags InnerFalutFlags;

volatile TLEDeviceCMD TLECMD;
volatile TLEDeviceCMD TLECMDTarget;
volatile TLEErrFlag TLEErrFlag_1;
volatile TLEErrFlag TLEErrFlag_2;
volatile unsigned char TLEFault1;
volatile unsigned char TLEFault2;
volatile unsigned char TLEErrorOUT[12];

/*
**********************************************************************
** ===================================================================
**                  CAN Parameters
** ===================================================================
**********************************************************************
*/
volatile unsigned char PrtCANTXD = 0;

//**MSG Buffers****MSG ID Index**********************************************************************************
volatile CAN_Message Msg_CAN_TXD[CAN_TXD_NUM], Msg_CAN_RXD[CAN_RXD_NUM];
volatile CAN_ID CAN_TXD_ID[CAN_TXD_NUM] = { ID_HCU2FCU_Msg1,ID_HCU2FCU_Msg2 };
volatile CAN_ID CAN_RXD_ID[CAN_RXD_NUM] = { ID_FCU2HCU_Msg};

/*
**********************************************************************
** ===================================================================
**                  Sys Temp Variables Parameters
** ===================================================================
**********************************************************************
*/
volatile int systemp_rev;
volatile int systemp_error;
volatile int systemp_H;
volatile int systemp_L;
volatile int systemp_Flag;
volatile int systemp_Timer1;
volatile int systemp_Timer2;
volatile int systemp_Timer3;
volatile int systemp_Timer4;


void SysParametersInit(void)
{
	int i;
	SetStatePowerUp;
	HCUStatus.MergedBits.ErrGrade = ErrorGradeOK;
	HCU_ErrorGrade_Current = ErrorGradeOK;
	HCU_ErrorCode.ErrorCode = ErrorCodeOK;
	HCU_ErrorCode_Current.ErrorCode = ErrorCodeOK;
	InnerFalutFlags.flags = 0x00;
	TaskFlags.flags = 0x0000;
	SystemADData_Int();
	CANMsgBuffersConfig();

	TLECMD.DriverCMD = 0xffff;
	TLECMDTarget.DriverCMD = 0xffff;
	TLEFault1 = 1;
	TLEFault2 = 1;
	TLEErrFlag_1.TLEErrFlag = 0xffff;
	TLEErrFlag_2.TLEErrFlag = 0xffff;

	//ErrorFlag
	for (i = 0; i < 5; i++)
	{	SysErrFlag.H2Con[i].ErrorFlag=ErrorFlagOK;	}
	for (i = 0; i < 6; i++)
	{	SysErrFlag.NTC[i].ErrorFlag = ErrorFlagOK;	}
	for (i = 0; i < 12; i++)
	{	SysErrFlag.TLEOUT[i].ErrorFlag = ErrorFlagOK;	}
	SysErrFlag.P_H2Mid.ErrorFlag = ErrorFlagOK;
	SysErrFlag.P_H2Tank.ErrorFlag = ErrorFlagOK;
	ErrorTimer_CAN = (0xff);

	systemp_Timer1=0;
	systemp_Timer2=0;
	systemp_Timer3=0;
	systemp_Timer4=0;
}

void SysInit(void)
{
	SysParametersInit();
	LED1_ON;
	LED2_ON;
	LED3_ON;
	LED4_ON;
	(void)ADCH_Measure(FALSE);
	(void)TI_20ms_Enable();
}


/**************************************************************************************
Function:       // CANMsgBuffersConfig
Called By:      // SysParametersInit
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void CANMsgBuffersConfig(void)
{
	unsigned char index,i;
	//****************CAN AcceptanceCode CAN AcceptanceMask*********
	(void)CAN_SetAcceptanceCode(CAN_AcceptanceCode1, CAN_AcceptanceCode2);
	(void)CAN_SetAcceptanceMask(CAN_AcceptanceMask1, CAN_AcceptanceMask2);
	//*****************CAN_TXD***************
	for (index = 0; index<CAN_TXD_NUM; index++)
	{
		for (i = 0; i < 8; i++)	Msg_CAN_TXD[index].data[i] = 0x00;
		Msg_CAN_TXD[index].ID = CAN_TXD_ID[index];
		Msg_CAN_TXD[index].FrameFormat = EXTENDED_FORMAT;
		Msg_CAN_TXD[index].FrameType = DATA_FRAME;
		Msg_CAN_TXD[index].length = 8;
	}
	//*****************CAN_RXD***************
	for (index = 0; index<CAN_RXD_NUM; index++)
	{
		for (i = 0; i < 8; i++)	Msg_CAN_RXD[index].data[i] = 0x00;
		Msg_CAN_RXD[index].ID = CAN_RXD_ID[index];
		Msg_CAN_RXD[index].FrameFormat = EXTENDED_FORMAT;
		Msg_CAN_RXD[index].FrameType = DATA_FRAME;
		Msg_CAN_RXD[index].length = 8;
	}
}
/**************************************************************************************
Function:       // SystemADData_Int
Called By:      // SysParametersInit
Input:          // NA
Return:         // NA
Others:         // NA
****************************************************************************************/
void SystemADData_Int(void)
{
	int i;
	for (i = 0; i < 6; i++)SYSTEM_AD_DATA.NTC_T[i] = 0;
	for (i = 0; i < 5; i++)SYSTEM_AD_DATA.H2Con[i] = 0;
	SYSTEM_AD_DATA.P_Mid = 0;
	SYSTEM_AD_DATA.P_Tank = 0;
}
