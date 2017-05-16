/*
 * DataType.h
 *
 *  Created on: Apr 27, 2017
 *      Author: YE_Chuan
 */

#ifndef DATATYPE_H_
#define DATATYPE_H_

 /*
 **********************************************************************
 ** ===================================================================
 **               Base state of ECU used for HCU
 ** ===================================================================
 **********************************************************************
 */
typedef union {
	unsigned char Status;
	struct {
		unsigned int BIT0 : 1;
		unsigned int BIT1 : 1;
		unsigned int BIT2 : 1;
		unsigned int BIT3 : 1;
		unsigned int BIT4 : 1;
		unsigned int BIT5 : 1;
		unsigned int BIT6 : 1;
		unsigned int BIT7 : 1;
	} Bits;
	struct {
		unsigned int ErrGrade		:	3;
		unsigned int StateMachine	:	3;
		unsigned int reserve1Bits	:	2;
	}MergedBits;
}StatusDef;
/*
**********************************************************************
** ===================================================================
**               Flag Type Defined in this programme
** ===================================================================
**********************************************************************
*/
typedef union {
	unsigned char flags;
	struct {
		unsigned int flag0         :1;                                       
		unsigned int flag1         :1;                                      
		unsigned int flag2         :1;                                      
		unsigned int flag3         :1;                                      
		unsigned int flag4         :1;                                      
		unsigned int flag5         :1;                                      
		unsigned int flag6         :1;                                       
		unsigned int flag7         :1;                                       
	} Bits;
}ByteFlags;

typedef union { 
	unsigned int flags;
	struct {
		unsigned int flag0         :1;                                       
		unsigned int flag1         :1;                                      
		unsigned int flag2         :1;                                      
		unsigned int flag3         :1;                                      
		unsigned int flag4         :1;                                      
		unsigned int flag5         :1;                                      
		unsigned int flag6         :1;                                       
		unsigned int flag7         :1;
		unsigned int flag8         :1;                                       
		unsigned int flag9         :1;                                      
		unsigned int flag10        :1;                                      
		unsigned int flag11        :1;                                      
		unsigned int flag12        :1;                                      
		unsigned int flag13        :1;                                      
		unsigned int flag14        :1;                                       
		unsigned int flag15        :1;                                       
	}Bits;
}WordFlags;
/*
**********************************************************************
** ===================================================================
**               TLE6232 command Defined in this programme
** ===================================================================
**********************************************************************
*/
/*** Control of Power Stages ***/
typedef union {
	unsigned int DriverCMD;
	struct {
		unsigned char DriverCMD1;
		unsigned char DriverCMD2;		
	}DriverCMDBytes;
	struct {
		unsigned  int reserv1 : 2;		 // reserved
		unsigned  int OUT2	: 1;		 // TLE1-OUT1
		unsigned  int OUT8	: 1;		 // TLE1-OUT2
		unsigned  int OUT10	: 1;		 // TLE1-OUT3
		unsigned  int OUT3	: 1;		 // TLE1-OUT4
		unsigned  int OUT9	: 1;		 // TLE1-OUT5
		unsigned  int OUT1	: 1;		 // TLE1-OUT6
		unsigned  int reserv2 : 2;		 // reserved
		unsigned  int OUT7	: 1;		 // TLE2-OUT1
		unsigned  int OUT5	: 1;		 // TLE2-OUT2
		unsigned  int OUT4	: 1;		 // TLE2-OUT3
		unsigned  int OUT11 : 1;		 // TLE2-OUT4
		unsigned  int OUT6	: 1;		 // TLE2-OUT5
		unsigned  int OUT12 : 1;		 // TLE2-OUT6
	}DriverCMDBits;
}TLEDeviceCMD;

typedef union {
	unsigned int TLEErrFlag;
	struct {
		unsigned char TLEErrFlagH;
		unsigned char TLEErrFlagL;
	}TLEErrBytes;
	struct {
		unsigned  int DIA5	: 2;		// diagnosis information of CH5
		unsigned  int DIA6	: 2;		// diagnosis information of CH6
		unsigned  int OT	: 1;		// diagnosis information of CHIP over temperature
		unsigned  int Fault : 1;		// diagnosis information of CHIP general fault
		unsigned  int resv	: 2;		// reserved
		unsigned  int DIA1	: 2;		// diagnosis information of CH1
		unsigned  int DIA2	: 2;		// diagnosis information of CH2
		unsigned  int DIA3	: 2;		// diagnosis information of CH3
		unsigned  int DIA4	: 2;		// diagnosis information of CH4
	}TLEErrBits;
}TLEErrFlag;

/*
**********************************************************************
** ===================================================================
**               CAN Message Defined in this programme
** ===================================================================
**********************************************************************
*/
typedef union {
	unsigned long ID;
	struct {
		unsigned char ID0;
		unsigned char ID1;
		unsigned char ID2;
		unsigned char ID3;
	}IDBYTES;
}CAN_ID;

typedef struct {
	CAN_ID ID;
	unsigned char data[8];
	unsigned char FrameType;
	unsigned char length;
	unsigned char FrameFormat;
}CAN_Message;

typedef union {
	unsigned char Data;
	struct 	{
		unsigned int BIT0 : 1;
		unsigned int BIT1 : 1;
		unsigned int BIT2 : 1;
		unsigned int BIT3 : 1;
		unsigned int BIT4 : 1;
		unsigned int BIT5 : 1;
		unsigned int BIT6 : 1;
		unsigned int BIT7 : 1;
	}Bits;
}Data_Bits8;


/*
**********************************************************************
** ===================================================================
**               AD Data for this programme
** ===================================================================
**********************************************************************
*/
typedef struct 
{
	unsigned char NTC_T[6];
	unsigned char H2Con[5];
	unsigned int P_Tank;
	unsigned int P_Mid;
}AD_Date;
/*
**********************************************************************
** ===================================================================
**               System Error
** ===================================================================
**********************************************************************
*/
/*
typedef union
{
	unsigned long System_Error[2];
	struct
	{
//#if HCU_Type == HCUA
		unsigned int TLEOUT1_OT		: 1;		//ErrorGradeAlarm
		unsigned int TLEOUT1_SG		: 1;		//ErrorGradeError
		unsigned int TLEOUT2_OT		: 1;		//ErrorGradeAlarm
		unsigned int TLEOUT2_SG		: 1;		//ErrorGradeError
		unsigned int TLEOUT3_OT		: 1;		//ErrorGradeAlarm
		unsigned int TLEOUT3_SG		: 1;		//ErrorGradeError
		unsigned int TLEOUT4_OT		: 1;		//ErrorGradeAlarm
		unsigned int TLEOUT4_SG		: 1;		//ErrorGradeError
		unsigned int TLEOUT5_OT		: 1;		//ErrorGradeAlarm
		unsigned int TLEOUT5_SG		: 1;		//ErrorGradeError
		unsigned int TLEOUT_ALL		: 1;		//ErrorGradeError

		unsigned int T_Tank1_OT75	: 1;		//ErrorGradeAlarm
		unsigned int T_Tank1_OT85	: 1;		//ErrorGradeError
		unsigned int T_Tank1_SENSOR	: 1;		//ErrorGradeError
		unsigned int T_Tank2_OT75	: 1;		//ErrorGradeAlarm
		unsigned int T_Tank2_OT85	: 1;		//ErrorGradeError
		unsigned int T_Tank2_SENSOR	: 1;		//ErrorGradeError
		unsigned int T_Tank3_OT75	: 1;		//ErrorGradeAlarm
		unsigned int T_Tank3_OT85	: 1;		//ErrorGradeError
		unsigned int T_Tank3_SENSOR	: 1;		//ErrorGradeError
		unsigned int T_Tank4_OT75	: 1;		//ErrorGradeAlarm
		unsigned int T_Tank4_OT85	: 1;		//ErrorGradeError
		unsigned int T_Tank4_SENSOR	: 1;		//ErrorGradeError
		unsigned int T_Tank5_OT75	: 1;		//ErrorGradeAlarm
		unsigned int T_Tank5_OT85	: 1;		//ErrorGradeError
		unsigned int T_Tank5_SENSOR	: 1;		//ErrorGradeError

		unsigned int H2Con1_Alarm		: 1;		//ErrorGradeAlarm
		unsigned int H2Con1_Emergency	: 1;		//ErrorGradeEmergency
		unsigned int H2Con1_Sensor		: 1;		//ErrorGradeEmergency
		unsigned int H2Con2_Alarm		: 1;		//ErrorGradeAlarm
		unsigned int H2Con2_Emergency	: 1;		//ErrorGradeEmergency
		unsigned int H2Con2_Sensor		: 1;		//ErrorGradeEmergency

		unsigned int CAN				: 1;		//ErrorGradeError
		unsigned int resv0				: 15;
		unsigned int resv1				: 16;
//#endif // HCU_Type == HCUA
#if HCU_Type == HCUB

		unsigned int TLEOUT1_OT			: 1;		//ErrorGradeAlarm
		unsigned int TLEOUT1_SG			: 1;		//ErrorGradeError
		unsigned int TLEOUT2_OT			: 1;		//ErrorGradeAlarm
		unsigned int TLEOUT2_SG			: 1;		//ErrorGradeError
		unsigned int TLEOUT_ALL			: 1;		//ErrorGradeError

		unsigned int T_Tank6_OT75		: 1;		//ErrorGradeAlarm
		unsigned int T_Tank6_OT85		: 1;		//ErrorGradeError
		unsigned int T_Tank6_SENSOR		: 1;		//ErrorGradeError
		unsigned int T_Tank7_OT75		: 1;		//ErrorGradeAlarm
		unsigned int T_Tank7_OT85		: 1;		//ErrorGradeError
		unsigned int T_Tank7_SENSOR		: 1;		//ErrorGradeError


		unsigned int H2Con3_Alarm		: 1;		//ErrorGradeAlarm
		unsigned int H2Con3_Emergency	: 1;		//ErrorGradeEmergency
		unsigned int H2Con3_Sensor		: 1;		//ErrorGradeEmergency
		unsigned int H2Con4_Alarm		: 1;		//ErrorGradeAlarm
		unsigned int H2Con4_Emergency	: 1;		//ErrorGradeEmergency
		unsigned int H2Con4_Sensor		: 1;		//ErrorGradeEmergency
		unsigned int H2Con5_Alarm		: 1;		//ErrorGradeAlarm
		unsigned int H2Con5_Emergency	: 1;		//ErrorGradeEmergency
		unsigned int H2Con5_Sensor		: 1;		//ErrorGradeEmergency
		unsigned int H2Con6_Alarm		: 1;		//ErrorGradeAlarm
		unsigned int H2Con6_Emergency	: 1;		//ErrorGradeEmergency
		unsigned int H2Con6_Sensor		: 1;		//ErrorGradeEmergency
		unsigned int H2Con7_Alarm		: 1;		//ErrorGradeAlarm
		unsigned int H2Con7_Emergency	: 1;		//ErrorGradeEmergency
		unsigned int H2Con7_Sensor		: 1;		//ErrorGradeEmergency

		unsigned int P_H2Tank_OP350		: 1;		//ErrorGradeError
		unsigned int P_H2Tank_Sensor	: 1;		//ErrorGradeEmergency
		unsigned int P_H2Mid_OP10		: 1;		//ErrorGradeError
		unsigned int P_H2Mid_LP7		: 1;		//ErrorGradeAlarm
		unsigned int P_H2Mid_Sensor		: 1;		//ErrorGradeError

		unsigned int CAN				: 1;		//ErrorGradeError
		unsigned long resv0;

#endif // HCU_Type == HCUB
	}Bits;
}SYSTEM_ERROR;

*/
#endif /* DATATYPE_H_ */
