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
 **                  System Type
 ** ===================================================================
 **********************************************************************
 */
#define HCUA (0)
#define HCUB (1)
#define HCU_Type HCUA

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
#define Task_TLE6232Update		TaskFlags.Bits.flag1//100ms ISR
#define Task_CANTXD				TaskFlags.Bits.flag2//After Timer_CAN=CAN_Send_Delay
#define Task_FCUCMD				TaskFlags.Bits.flag3//CAN REV ISR
#define Task_TLE6232CMDSet		TaskFlags.Bits.flag4//100ms ISR
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
#define T_Tank1		SYSTEM_AD_DATA.NTC_T[0]
#define T_Tank2		SYSTEM_AD_DATA.NTC_T[1]
#define T_Tank3		SYSTEM_AD_DATA.NTC_T[2]
#define T_Tank4		SYSTEM_AD_DATA.NTC_T[3]
#define T_Tank5		SYSTEM_AD_DATA.NTC_T[4]
#define H2Con1		SYSTEM_AD_DATA.H2Con[0]
#define H2Con2		SYSTEM_AD_DATA.H2Con[1]
#elif HCU_Type==HCUB
#define T_Tank6		(SYSTEM_AD_DATA.NTC_T[0])
#define T_Tank7		(SYSTEM_AD_DATA.NTC_T[1])
#define H2Con3		(SYSTEM_AD_DATA.H2Con[0])
#define H2Con4		(SYSTEM_AD_DATA.H2Con[1])
#define H2Con5		(SYSTEM_AD_DATA.H2Con[2])
#define H2Con6		(SYSTEM_AD_DATA.H2Con[3])
#define H2Con7		(SYSTEM_AD_DATA.H2Con[4])
#define P_H2Tank	(SYSTEM_AD_DATA.P_Tank)
#define P_H2Mid		(SYSTEM_AD_DATA.P_Mid)
#endif

#define RawData_NTC_T0	(ADCHRawData[0])	//NTC1
#define RawData_NTC_T1	(ADCHRawData[1])	//NTC2
#define RawData_NTC_T2	(ADCHRawData[2])	//NTC3
#define RawData_NTC_T3	(ADCHRawData[3])	//NTC4
#define RawData_NTC_T4	(ADCHRawData[4])	//NTC5
#define RawData_NTC_T5	(ADCHRawData[5])	//NTC6

#define RawData_P_H2Tank	(ADCHRawData[8])	//AD1
#define RawData_P_H2Mid		(ADCHRawData[9])	//AD2

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
#define P_H2TankDataRawLimitH (3932)	//480barg 
#define P_H2TankDataRawLimitL (614)		//<3mA sensor error

#define P_H2MidData_Table_Len (2)
extern const unsigned int P_H2MidRawData_Table[P_H2MidData_Table_Len];
extern const unsigned int P_H2MidData_Table[P_H2MidData_Table_Len];
#define P_H2MidDataRawLimitH (3686) 	//18barg
#define P_H2MidDataRawLimitL (614)		//<3mA sensor error



/*
**********************************************************************
** ===================================================================
**                  System Status
** ===================================================================
**********************************************************************
*/
extern volatile StatusDef		HCUStatus;
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
#define ErrorGradeOK			(0)
#define ErrorGradeWarning		(1)
#define	ErrorGradeAlarm			(2)
#define	ErrorGradeError			(4)
#define	ErrorGradeEmergency		(7)
/*
**********************************************************************
** ===================================================================
**                  System Error Code
** ===================================================================
**********************************************************************
*/
extern volatile unsigned char HCU_ErrorCode;
//extern volatile SYSTEM_ERROR SystemError;
#if  HCU_Type==HCUA

#define ErrorCode_TLEOUT1_OT		(0)		//ErrorGradeAlarm
#define ErrorCode_TLEOUT1_SG		(0)		//ErrorGradeError
#define ErrorCode_TLEOUT2_OT		(0)		//ErrorGradeAlarm
#define ErrorCode_TLEOUT2_SG		(0)		//ErrorGradeError
#define ErrorCode_TLEOUT3_OT		(0)		//ErrorGradeAlarm
#define ErrorCode_TLEOUT3_SG		(0)		//ErrorGradeError
#define ErrorCode_TLEOUT4_OT		(0)		//ErrorGradeAlarm
#define ErrorCode_TLEOUT4_SG		(0)		//ErrorGradeError
#define ErrorCode_TLEOUT5_OT		(0)		//ErrorGradeAlarm
#define ErrorCode_TLEOUT5_SG		(0)		//ErrorGradeError
#define ErrorCode_TLEOUT_ALL		(0)		//ErrorGradeError

#define ErrorCode_T_Tank1_OT75		(0)		//ErrorGradeAlarm
#define ErrorCode_T_Tank1_OT85		(0)		//ErrorGradeError
#define ErrorCode_T_Tank1_SENSOR	(0)		//ErrorGradeError
#define ErrorCode_T_Tank2_OT75		(0)		//ErrorGradeAlarm
#define ErrorCode_T_Tank2_OT85		(0)		//ErrorGradeError
#define ErrorCode_T_Tank2_SENSOR	(0)		//ErrorGradeError
#define ErrorCode_T_Tank3_OT75		(0)		//ErrorGradeAlarm
#define ErrorCode_T_Tank3_OT85		(0)		//ErrorGradeError
#define ErrorCode_T_Tank3_SENSOR	(0)		//ErrorGradeError
#define ErrorCode_T_Tank4_OT75		(0)		//ErrorGradeAlarm
#define ErrorCode_T_Tank4_OT85		(0)		//ErrorGradeError
#define ErrorCode_T_Tank4_SENSOR	(0)		//ErrorGradeError
#define ErrorCode_T_Tank5_OT75		(0)		//ErrorGradeAlarm
#define ErrorCode_T_Tank5_OT85		(0)		//ErrorGradeError
#define ErrorCode_T_Tank5_SENSOR	(0)		//ErrorGradeError

#define ErrorCode_H2Con1_Alarm		(0)		//ErrorGradeAlarm
#define ErrorCode_H2Con1_Emergency	(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con1_Sensor		(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con2_Alarm		(0)		//ErrorGradeAlarm
#define ErrorCode_H2Con2_Emergency	(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con2_Sensor		(0)		//ErrorGradeEmergency

#define ErrorCode_CAN				(0)		//ErrorGradeError

#endif //  HCU_Type==HCUA

#if HCU_Type==HCUB

#define ErrorCode_TLEOUT1_OT		(0)		//ErrorGradeAlarm
#define ErrorCode_TLEOUT1_SG		(0)		//ErrorGradeError
#define ErrorCode_TLEOUT2_OT		(0)		//ErrorGradeAlarm
#define ErrorCode_TLEOUT2_SG		(0)		//ErrorGradeError
#define ErrorCode_TLEOUT_ALL		(0)		//ErrorGradeError

#define ErrorCode_T_Tank6_OT75		(0)		//ErrorGradeAlarm
#define ErrorCode_T_Tank6_OT85		(0)		//ErrorGradeError
#define ErrorCode_T_Tank6_SENSOR	(0)		//ErrorGradeError
#define ErrorCode_T_Tank7_OT75		(0)		//ErrorGradeAlarm
#define ErrorCode_T_Tank7_OT85		(0)		//ErrorGradeError
#define ErrorCode_T_Tank7_SENSOR	(0)		//ErrorGradeError


#define ErrorCode_H2Con3_Alarm		(0)		//ErrorGradeAlarm
#define ErrorCode_H2Con3_Emergency	(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con3_Sensor		(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con4_Alarm		(0)		//ErrorGradeAlarm
#define ErrorCode_H2Con4_Emergency	(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con4_Sensor		(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con5_Alarm		(0)		//ErrorGradeAlarm
#define ErrorCode_H2Con5_Emergency	(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con5_Sensor		(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con6_Alarm		(0)		//ErrorGradeAlarm
#define ErrorCode_H2Con6_Emergency	(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con6_Sensor		(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con7_Alarm		(0)		//ErrorGradeAlarm
#define ErrorCode_H2Con7_Emergency	(0)		//ErrorGradeEmergency
#define ErrorCode_H2Con7_Sensor		(0)		//ErrorGradeEmergency

#define ErrorCode_P_H2Tank_OP350	(0)		//ErrorGradeError
#define ErrorCode_P_H2Tank_Sensor	(0)		//ErrorGradeEmergency
#define ErrorCode_P_H2Mid_OP10		(0)		//ErrorGradeError
#define ErrorCode_P_H2Mid_LP7		(0)		//ErrorGradeAlarm
#define ErrorCode_P_H2Mid_Sensor	(0)		//ErrorGradeError

#define ErrorCode_CAN				(0)		//ErrorGradeError

#endif // HCU_Type==HCUB



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


extern volatile TLEDeviceCMD TLECMD;
extern volatile TLEDeviceCMD TLECMDTarget;
extern volatile	TLEErrFlag TLEErrFlag_1;
extern volatile	TLEErrFlag TLEErrFlag_2;
extern volatile unsigned char TLEFault1;
extern volatile unsigned char TLEFault2;

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



void SysParametersInit(void);
void SysInit(void);
void CANMsgBuffersConfig(void);
void SystemADData_Int(void);




#endif /* SYSPARAMETERS_H_ */
