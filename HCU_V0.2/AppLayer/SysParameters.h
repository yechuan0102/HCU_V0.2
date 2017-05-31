/*
 * SysParameters.h
 *
 *  Created on: Apr 27, 2017
 *      Author: YE_Chuan
 */

#ifndef SYSPARAMETERS_H_
#define SYSPARAMETERS_H_



 /*
 **********************************************************************
 ** ===================================================================
 **                  TaskFlags
 ** ===================================================================
 **********************************************************************
 */
extern volatile WordFlags TaskFlags;
extern volatile unsigned char Timer_100ms; 
extern volatile unsigned char Timer_CAN;

#define Task_ADCHS				TaskFlags.Bits.flag0//ADC OnEnd ISR
#define Task_TLE6232			TaskFlags.Bits.flag1//100ms ISR
#define Task_CANTXD				TaskFlags.Bits.flag2//After Timer_CAN=CAN_Send_Delay
#define Task_FCUCMD				TaskFlags.Bits.flag3//CAN REV ISR
#define	Task_ADreStart			TaskFlags.Bits.flag4//ADC InnerFault 20ms ISR
#define Task_ErrorDiagnosis		TaskFlags.Bits.flag5//ADC OnEnd ISR

/*
**********************************************************************
** ===================================================================
**                  AD Channel Parameters
** ===================================================================
**********************************************************************
*/
extern volatile unsigned int  ADCHRawData[16];
extern volatile AD_Date SYSTEM_AD_DATA;
#if HCU_Type==HCUA
#define PhysData_T_Tank1		SYSTEM_AD_DATA.NTC_T[0]
#define PhysData_T_Tank2		SYSTEM_AD_DATA.NTC_T[1]
#define PhysData_T_Tank3		SYSTEM_AD_DATA.NTC_T[2]
#define PhysData_T_Tank4		SYSTEM_AD_DATA.NTC_T[3]
#define PhysData_T_Tank5		SYSTEM_AD_DATA.NTC_T[4]
#define PhysData_H2Con1			SYSTEM_AD_DATA.H2Con[0]
#define PhysData_H2Con2			SYSTEM_AD_DATA.H2Con[1]
#elif HCU_Type==HCUB
#define PhysData_T_Tank6		(SYSTEM_AD_DATA.NTC_T[0])
#define PhysData_T_Tank7		(SYSTEM_AD_DATA.NTC_T[1])
#define PhysData_H2Con3			(SYSTEM_AD_DATA.H2Con[0])
#define PhysData_H2Con4			(SYSTEM_AD_DATA.H2Con[1])
#define PhysData_H2Con5			(SYSTEM_AD_DATA.H2Con[2])
#define PhysData_H2Con6			(SYSTEM_AD_DATA.H2Con[3])
#define PhysData_H2Con7			(SYSTEM_AD_DATA.H2Con[4])
#define PhysData_P_H2Tank		(SYSTEM_AD_DATA.P_Tank)
#define PhysData_P_H2Mid		(SYSTEM_AD_DATA.P_Mid)
#endif

#define RawData_NTC_T0	(ADCHRawData[0])	//NTC1
#define RawData_NTC_T1	(ADCHRawData[1])	//NTC2
#define RawData_NTC_T2	(ADCHRawData[2])	//NTC3
#define RawData_NTC_T3	(ADCHRawData[3])	//NTC4
#define RawData_NTC_T4	(ADCHRawData[4])	//NTC5
#define RawData_NTC_T5	(ADCHRawData[5])	//NTC6

#define RawData_P_H2Mid		(ADCHRawData[8])	//AD1
#define RawData_P_H2Tank	(ADCHRawData[9])	//AD2

#define RawData_H2Con0	(ADCHRawData[10])	//AD3
#define RawData_H2Con1	(ADCHRawData[11])	//AD4
#define RawData_H2Con2	(ADCHRawData[12])	//AD5
#define RawData_H2Con3	(ADCHRawData[6])	//AD6
#define RawData_H2Con4	(ADCHRawData[7])	//AD7




#define TData_Table_Len		(39)
extern const unsigned int TRawData_Table[TData_Table_Len];
extern const unsigned int TData_Table[TData_Table_Len];
#define TDataRawLimitH (4028)			//>150C sensor error
#define TDataRawLimitL (302)			//<-40C	sensor error

#define H2ConData_Table_Len (2)
extern const unsigned int H2ConRawData_Table[H2ConData_Table_Len];
extern const unsigned int H2ConData_Table[H2ConData_Table_Len];
#define H2ConRawLimitH (3932)			//>4.8V sensor error
#define H2ConRawLimitL (164)			//<0.2V sensor error

#define P_H2TankData_Table_Len (2)
extern const unsigned int P_H2TankRawData_Table[P_H2TankData_Table_Len];
extern const unsigned int P_H2TankData_Table[P_H2TankData_Table_Len];
#define P_H2TankDataRawLimitH (3962)	//480barg 
#define P_H2TankDataRawLimitL (614)		//<3mA sensor error

#define P_H2MidData_Table_Len (2)
extern const unsigned int P_H2MidRawData_Table[P_H2MidData_Table_Len];
extern const unsigned int P_H2MidData_Table[P_H2MidData_Table_Len];
#define P_H2MidDataRawLimitH (3768) 	//18barg
#define P_H2MidDataRawLimitL (614)		//<3mA sensor error



/*
**********************************************************************
** ===================================================================
**                  System Status
** ===================================================================
**********************************************************************
*/
extern volatile StatusDef HCUStatus;
extern volatile unsigned char HCU_ErrorGrade_Current;
/*******************System State macro**************************/
#define StatePowerUp    	(1)
#define StateReady 			(2)
#define StateEnable       	(3)
#define StateError         	(4)
#define StateCalib			(6)
#define StateDebug			(7)


#define IsStatePowerUp  		(HCUStatus.MergedBits.StateMachine==StatePowerUp)
#define IsStateReady    		(HCUStatus.MergedBits.StateMachine==StateReady)
#define IsStateEnable     		(HCUStatus.MergedBits.StateMachine==StateEnable)
#define IsStateError         	(HCUStatus.MergedBits.StateMachine==StateError)
#define IsStateCalib         	(HCUStatus.MergedBits.StateMachine==StateCalib)
#define IsStateDebug         	(HCUStatus.MergedBits.StateMachine==StateDebug)

#define SetStatePowerUp			(HCUStatus.MergedBits.StateMachine=StatePowerUp)
#define SetStateReady      		(HCUStatus.MergedBits.StateMachine=StateReady)
#define SetStateEnable			(HCUStatus.MergedBits.StateMachine=StateEnable)
#define SetStateError			(HCUStatus.MergedBits.StateMachine=StateError)
#define SetStateCalib 			(HCUStatus.MergedBits.StateMachine=StateError)
#define SetStateDebug   		(HCUStatus.MergedBits.StateMachine=StateError)

/*******************System Error macro**************************/
#define ErrorGradeOK			(0U)
#define ErrorGradeWarning		(1U)
#define	ErrorGradeAlarm			(2U)
#define	ErrorGradeError			(4U)
#define	ErrorGradeEmergency		(7U)
/*
**********************************************************************
** ===================================================================
**                  System Error Code
** ===================================================================
**********************************************************************
*/
extern volatile HCU_ERROR_CODE HCU_ErrorCode;
extern volatile HCU_ERROR_CODE HCU_ErrorCode_Current;
#define ErrorCodeOK						(0x00U)		//ErrorGradeOK

#define ErrorCode_CAN					(0x9FU)		//ErrorGradeError
#define ErrorCode_TLEOUT_OT_Part		(0x54U)		//ErrorGradeAlarm
#define ErrorCode_TLEOUT_OT_All			(0x92U)		//ErrorGradeError
#define ErrorCode_TLEOUT_SCG			(0x91U)		//ErrorGradeError

#define ErrorCode_T_Tank_OTAlarm		(0x4CU)		//ErrorGradeAlarm >75 deg C
#define ErrorCode_T_Tank_OTError		(0xECU)		//ErrorGradeError >85 deg C or all >75 deg C
#define ErrorCode_T_Tank_SENSOR			(0xEDU)		//ErrorGradeError

#define ErrorCode_StoH2Con_Alarm		(0x48U)		//ErrorGradeAlarm
#define ErrorCode_StoH2Con_Emergency	(0xE8U)		//ErrorGradeEmergency
#define ErrorCode_StoH2Con_Sensor		(0xE9U)		//ErrorGradeEmergency
#define ErrorCode_EngineH2Con_Alarm		(0x4AU)		//ErrorGradeAlarm
#define ErrorCode_EngineH2Con_Emergency	(0xEAU)		//ErrorGradeEmergency
#define ErrorCode_EngineH2Con_Sensor	(0xEBU)		//ErrorGradeEmergency
#define ErrorCode_CabinH2Con_Alarm		(0x4CU)		//ErrorGradeAlarm
#define ErrorCode_CabinH2Con_Emergency	(0xECU)		//ErrorGradeEmergency
#define ErrorCode_CabinH2Con_Sensor		(0xEDU)		//ErrorGradeEmergency

#define ErrorCode_P_H2Mid_H				(0x9AU)		//ErrorGradeError
#define ErrorCode_P_H2Mid_L				(0x5AU)		//ErrorGradeAlarm
#define ErrorCode_P_H2Mid_Sensor		(0x9BU)		//ErrorGradeError

#define	ErrorCode_P_H2Tank_H			(0x9CU)		//ErrorGradeError
#define ErrorCode_P_H2Tank_Sensor		(0xFCU)		//ErrorGradeEmergency

/*
**********************************************************************
** ===================================================================
**                  System Error Flag
** ===================================================================
**********************************************************************
*/
extern volatile SYSTEM_ERROR_FLAG SysErrFlag;
extern volatile unsigned char ErrorTimer_CAN;

#define ErrorFlag_TLEOUT1	(SysErrFlag.TLEOUT[0])
#define ErrorFlag_TLEOUT2	(SysErrFlag.TLEOUT[1])
#define ErrorFlag_TLEOUT3	(SysErrFlag.TLEOUT[2])
#define ErrorFlag_TLEOUT4	(SysErrFlag.TLEOUT[3])
#define ErrorFlag_TLEOUT5	(SysErrFlag.TLEOUT[4])
#define ErrorFlag_TLEOUT6	(SysErrFlag.TLEOUT[5])
#define ErrorFlag_TLEOUT7	(SysErrFlag.TLEOUT[6])
#define ErrorFlag_TLEOUT8	(SysErrFlag.TLEOUT[7])
#define ErrorFlag_TLEOUT9	(SysErrFlag.TLEOUT[8])
#define ErrorFlag_TLEOUT10	(SysErrFlag.TLEOUT[9])
#define ErrorFlag_TLEOUT11	(SysErrFlag.TLEOUT[10])
#define ErrorFlag_TLEOUT12	(SysErrFlag.TLEOUT[11])

#define ErrorFlag_NTC1		(SysErrFlag.NTC[0])
#define ErrorFlag_NTC2		(SysErrFlag.NTC[1])
#define ErrorFlag_NTC3		(SysErrFlag.NTC[2])
#define ErrorFlag_NTC4		(SysErrFlag.NTC[3])
#define ErrorFlag_NTC5		(SysErrFlag.NTC[4])
#define ErrorFlag_NTC6		(SysErrFlag.NTC[5])

#define ErrorFlag_H2Con1	(SysErrFlag.H2Con[0])
#define ErrorFlag_H2Con2	(SysErrFlag.H2Con[1])
#define ErrorFlag_H2Con3	(SysErrFlag.H2Con[2])
#define ErrorFlag_H2Con4	(SysErrFlag.H2Con[3])
#define ErrorFlag_H2Con5	(SysErrFlag.H2Con[4])

#define ErrorFlag_P_H2Tank	(SysErrFlag.P_H2Tank)
#define ErrorFlag_P_H2Mid	(SysErrFlag.P_H2Mid)

#define ErrorFlag_CAN		(SysErrFlag.CAN)

#define ErrorFlagOK				(0x00U)

/*Error Type*/
#define ERRTypeOK				(0U)		//ErrorGradeEmergency

#define ERRTypeTLEOT			(1U)		//ErrorGradeAlarm
#define ERRTypeTLEOL			(2U)		//ErrorGradeAlarm
#define	ERRTypeTLESCG			(3U)		//ErrorGradeError

#define ERRTypeH2Con_Alarm		(1U)		//ErrorGradeAlarm
#define ERRTypeH2Con_Emergency	(2U)		//ErrorGradeEmergency
#define ERRTypeH2Con_Sensor		(3U)		//ErrorGradeEmergency

#define ERRTypeNTC_OTAlarm		(1U)		//ErrorGradeAlarm
#define	ERRTypeNTC_OTError		(2U)		//ErrorGradeError
#define	ERRTypeNTC_Sensor		(3U)		//ErrorGradeError

#define ERRTypeP_H2Mid_H		(1U)		//ErrorGradeError
#define ERRTypeP_H2Mid_L		(2U)		//ErrorGradeAlarm
#define ERRTypeP_H2Mid_Sensor	(3U)		//ErrorGradeError

#define	ERRTypeP_H2Tank_H		(1U)		//ErrorGradeError
#define ERRTypeP_H2Tank_Sensor	(3U)		//ErrorGradeEmergency

#define ERRTypeCAN				(1U)		//ErrorGradeError

#define NTC_T_LimitH		(45U) //85 deg C
#define NTC_T_LimitL		(35U) //75 deg C
#define NTC_T_Rev			(33U) //73 deg C

#define H2Con_StoLimitH		(90U) //18000ppm
#define H2Con_StoLimitL		(50U) //10000ppm
#define H2Con_StoLimitRev	(25U) //5000ppm

#define H2Con_EngineLimitH	(20U) //4000ppm
#define H2Con_EngineLimitL	(10U) //2000ppm
#define H2Con_EngineRev		(5U)  //1000ppm

#define H2Con_CabinLimitH	(20U) //4000ppm
#define H2Con_CabinLimitL	(10U) //2000ppm
#define H2Con_CabinRev		(5U)  //1000ppm

#define P_H2Tank_Limit		(35000U) //350barg
#define P_H2Mid_LimitH		(1000U)	 //10barg
#define P_H2Mid_LimitL		(700U)   //7barg
#define P_H2Mid_RevL		(750U)   //7.5barg

#define Error_2s			(100U)
#define Error_5s			(250U)

/*
**********************************************************************
** ===================================================================
**                  InnerFalutFlags
** ===================================================================
**********************************************************************
*/
extern volatile WordFlags InnerFalutFlags;
#define InnerFault_ADProcess	(InnerFalutFlags.Bits.flag0)	//Fault flag for AD conversion Process
#define InnerFault_SPIPorcess	(InnerFalutFlags.Bits.flag1)	//Fault flag for SPI driver update Process

/*
**********************************************************************
** ===================================================================
**                  TLE Parameters
** ===================================================================
**********************************************************************
*/

#define TLE_1		(0U)
#define TLE_2		(1U)

#define TLE_WR_SCON			(0x98U)
#define TLE_RD_SCON			(0x94U)
#define TLE_WR_MUX			(0xA8U)
#define TLE_RD_MUX			(0xA4U)
#define TLE_RD_DIAG			(0x80U)
#define TLE_SET_MUX_SER		(0x03U)
#define TLE_NULL			(0x00U)

#define TLE_OUT_ON			(0U)
#define	TLE_OUT_OFF			(1U)

#define TLE_OUT1_ON			(TLECMD.DriverCMDBits.OUT1 = TLE_OUT_ON)
#define TLE_OUT2_ON			(TLECMD.DriverCMDBits.OUT2 = TLE_OUT_ON)
#define TLE_OUT3_ON			(TLECMD.DriverCMDBits.OUT3 = TLE_OUT_ON)
#define TLE_OUT4_ON			(TLECMD.DriverCMDBits.OUT4 = TLE_OUT_ON)
#define TLE_OUT5_ON			(TLECMD.DriverCMDBits.OUT5 = TLE_OUT_ON)
#define TLE_OUT6_ON			(TLECMD.DriverCMDBits.OUT6 = TLE_OUT_ON)
#define TLE_OUT7_ON			(TLECMD.DriverCMDBits.OUT7 = TLE_OUT_ON)
#define TLE_OUT8_ON			(TLECMD.DriverCMDBits.OUT8 = TLE_OUT_ON)
#define TLE_OUT9_ON			(TLECMD.DriverCMDBits.OUT9 = TLE_OUT_ON)
#define TLE_OUT10_ON		(TLECMD.DriverCMDBits.OUT10 = TLE_OUT_ON)
#define TLE_OUT11_ON		(TLECMD.DriverCMDBits.OUT11 = TLE_OUT_ON)
#define TLE_OUT12_ON		(TLECMD.DriverCMDBits.OUT12 = TLE_OUT_ON)

#define TLE_OUT1_OFF		(TLECMD.DriverCMDBits.OUT1 = TLE_OUT_OFF)
#define TLE_OUT2_OFF		(TLECMD.DriverCMDBits.OUT2 = TLE_OUT_OFF)
#define TLE_OUT3_OFF		(TLECMD.DriverCMDBits.OUT3 = TLE_OUT_OFF)
#define TLE_OUT4_OFF		(TLECMD.DriverCMDBits.OUT4 = TLE_OUT_OFF)
#define TLE_OUT5_OFF		(TLECMD.DriverCMDBits.OUT5 = TLE_OUT_OFF)
#define TLE_OUT6_OFF		(TLECMD.DriverCMDBits.OUT6 = TLE_OUT_OFF)
#define TLE_OUT7_OFF		(TLECMD.DriverCMDBits.OUT7 = TLE_OUT_OFF)
#define TLE_OUT8_OFF		(TLECMD.DriverCMDBits.OUT8 = TLE_OUT_OFF)
#define TLE_OUT9_OFF		(TLECMD.DriverCMDBits.OUT9 = TLE_OUT_OFF)
#define TLE_OUT10_OFF		(TLECMD.DriverCMDBits.OUT10 = TLE_OUT_OFF)
#define TLE_OUT11_OFF		(TLECMD.DriverCMDBits.OUT11 = TLE_OUT_OFF)
#define TLE_OUT12_OFF		(TLECMD.DriverCMDBits.OUT12 = TLE_OUT_OFF)

#define isTLE_OUT1_ON		(TLECMD.DriverCMDBits.OUT1 == TLE_OUT_ON)
#define isTLE_OUT2_ON		(TLECMD.DriverCMDBits.OUT2 == TLE_OUT_ON)
#define isTLE_OUT3_ON		(TLECMD.DriverCMDBits.OUT3 == TLE_OUT_ON)
#define isTLE_OUT4_ON		(TLECMD.DriverCMDBits.OUT4 == TLE_OUT_ON)
#define isTLE_OUT5_ON		(TLECMD.DriverCMDBits.OUT5 == TLE_OUT_ON)
#define isTLE_OUT6_ON		(TLECMD.DriverCMDBits.OUT6 == TLE_OUT_ON)
#define isTLE_OUT7_ON		(TLECMD.DriverCMDBits.OUT7 == TLE_OUT_ON)
#define isTLE_OUT8_ON		(TLECMD.DriverCMDBits.OUT8 == TLE_OUT_ON)
#define isTLE_OUT9_ON		(TLECMD.DriverCMDBits.OUT9 == TLE_OUT_ON)
#define isTLE_OUT10_ON		(TLECMD.DriverCMDBits.OUT10 == TLE_OUT_ON)
#define isTLE_OUT11_ON		(TLECMD.DriverCMDBits.OUT11 == TLE_OUT_ON)
#define isTLE_OUT12_ON		(TLECMD.DriverCMDBits.OUT12 == TLE_OUT_ON)

#define isTLE_OUT1_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT1 == TLE_OUT_ON)
#define isTLE_OUT2_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT2 == TLE_OUT_ON)
#define isTLE_OUT3_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT3 == TLE_OUT_ON)
#define isTLE_OUT4_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT4 == TLE_OUT_ON)
#define isTLE_OUT5_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT5 == TLE_OUT_ON)
#define isTLE_OUT6_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT6 == TLE_OUT_ON)
#define isTLE_OUT7_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT7 == TLE_OUT_ON)
#define isTLE_OUT8_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT8 == TLE_OUT_ON)
#define isTLE_OUT9_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT9 == TLE_OUT_ON)
#define isTLE_OUT10_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT10 == TLE_OUT_ON)
#define isTLE_OUT11_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT11 == TLE_OUT_ON)
#define isTLE_OUT12_CMD_ON		(TLECMDTarget.DriverCMDBits.OUT12 == TLE_OUT_ON)


#define TLE_SEND_FAILED		(0x8000U)

#define SPIWaitStepLimit 8000U   //when SPI operation the wait time limit to 8000 cycles

#if HCU_Type == HCUA
#define TLEERRORMASK_1 (0x10C3U)
#define TLEERRORMASK_2 (0x103FU)
#endif // 0
#if HCU_Type == HCUB
#define TLEERRORMASK_1 (0x10C3U)
#define TLEERRORMASK_2 (0x0000U)
#endif // 0


#define TLEErrorOK			(3U)
#define TLEErrorOT			(2U)
#define TLEErrorOL			(1U)
#define TLEErrorSCG			(0U)

extern volatile TLEDeviceCMD TLECMD;
extern volatile TLEDeviceCMD TLECMDTarget;
extern volatile	TLEErrFlag TLEErrFlag_1;
extern volatile	TLEErrFlag TLEErrFlag_2;
extern volatile unsigned char TLEFault1;
extern volatile unsigned char TLEFault2;
extern volatile unsigned char TLEErrorOUT[12];

/*
**********************************************************************
** ===================================================================
**                 Configuration of the CAN Parameters
** ===================================================================
**********************************************************************
*/

#define DisableCANTXD  (CANTIER=0x00)
#define EnableCANTXD   (CANTIER=0x07)

extern volatile unsigned char PrtCANTXD;
/****** CAN AcceptanceMask AcceptanceCode******/
#if HCU_Type==HCUA
#define CAN_AcceptanceMask1		(0x00000000)
#define CAN_AcceptanceMask2		(0x00000000)
#define CAN_AcceptanceCode1		(0x07FE4002)
#define CAN_AcceptanceCode2		(0x00000000)
#endif // HCU_Type==HCUA    ID:0x00FF2001

#if HCU_Type==HCUB
#define CAN_AcceptanceMask1		(0x00000000)
#define CAN_AcceptanceMask2		(0x00000000)
#define CAN_AcceptanceCode1		(0x07FE4202)
#define CAN_AcceptanceCode2		(0x00000000)
#endif // HCU_Type==HCUB    ID:0x00FF2101

/*********Constant used by CAN,include CAN Msg nums,ID,ID Index**************************/
/****************************CAN MSG Nums************************************************/
#define CAN_TXD_NUM		(2)
#define CAN_RXD_NUM		(1)
#define HCU2FCU_Msg1	(0)
#define HCU2FCU_Msg2	(1)
#define FCU2HCU_Msg     (0) 
/************************CAN Frame**************/
extern volatile CAN_Message MsgSendCAN[CAN_TXD_NUM], MsgRecvCAN[CAN_RXD_NUM];
/**************HCU To FCU***********************/
#if  HCU_Type==HCUA
#define ID_HCU2FCU_Msg1    (0x18FF2010)
#define ID_HCU2FCU_Msg2    (0x18FF2020)
//  HCU_Type==HCUA
#elif HCU_Type==HCUB
#define ID_HCU2FCU_Msg1    (0x18FF2110)
#define ID_HCU2FCU_Msg2    (0x18FF2120)
#endif // HCU_Type==HCUB

/**************FCU TO HCU***********************/
#if  HCU_Type==HCUA
#define ID_FCU2HCU_Msg    (0x00FF2001)
//  HCU_Type==HCUA
#elif  HCU_Type==HCUB
#define ID_FCU2HCU_Msg    (0x00FF2101)
#endif //  HCU_Type==HCUB
/*************CAN Send Delay*******************/

#if  HCU_Type==HCUA
#define CAN_Send_Delay		(30)	//  HCU_Type==HCUA
#elif  HCU_Type==HCUB
#define CAN_Send_Delay		(33)	//  HCU_Type==HCUB
#endif 
/**********MSG Buffers****MSG ID Index***********/
extern volatile CAN_Message Msg_CAN_TXD[CAN_TXD_NUM], Msg_CAN_RXD[CAN_RXD_NUM];
extern volatile CAN_ID CAN_TXD_ID[CAN_TXD_NUM];
extern volatile CAN_ID CAN_RXD_ID[CAN_RXD_NUM];

/*
**********************************************************************
** ===================================================================
**               LED Parameters
** ===================================================================
**********************************************************************
*/
#define LED1_ON		LED1_SetVal()
#define LED2_ON		LED2_SetVal()
#define LED3_ON		LED3_SetVal()
#define LED4_ON		LED4_SetVal()

#define LED1_OFF	LED1_ClrVal()
#define LED2_OFF	LED2_ClrVal()
#define LED3_OFF	LED3_ClrVal()
#define LED4_OFF	LED4_ClrVal()

/*
**********************************************************************
** ===================================================================
**                  Sys Temp Variables Parameters
** ===================================================================
**********************************************************************
*/
extern volatile int systemp_rev;
extern volatile int systemp_error;
extern volatile int systemp_H;
extern volatile int systemp_L;
extern volatile int systemp_Flag;
extern volatile int systemp_Timer1;
extern volatile int systemp_Timer2;
extern volatile int systemp_Timer3;
extern volatile int systemp_Timer4;


void SysParametersInit(void);
void SysInit(void);
void CANMsgBuffersConfig(void);
void SystemADData_Int(void);




#endif /* SYSPARAMETERS_H_ */
