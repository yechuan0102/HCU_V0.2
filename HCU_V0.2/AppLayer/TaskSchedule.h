/*
 * TaskSchedule.h
 *
 *  Created on: Apr 27, 2017
 *      Author: YE_Chuan
 */

#ifndef TASKSCHEDULE_H_
#define TASKSCHEDULE_H_

/*
**********************************************************************
** ===================================================================
**        Tasks Defined in This Programme
** ===================================================================
**********************************************************************
*/
void TaskSchedule(void);
void Task_ADCHSProcess(void);
unsigned char Calc_ADData_NTC(unsigned int Temp_RawData);
unsigned char Calc_ADData_H2Con(unsigned int Temp_RawData);
unsigned int Calc_ADData_P_H2Tank(unsigned int Temp_RawData);
unsigned int Calc_ADData_P_H2Mid(unsigned int Temp_RawData);
unsigned int AD_Lagrange(const unsigned int x[], const unsigned int y[], const int len,unsigned int xh);

unsigned int TLE_SPI_SendCMD(unsigned char ControlByte, unsigned char DataByte ,unsigned int TLEType);
void TLECMD_Open1Channel(void);
void TLECMD_Close1Channel(void);
void TLE_CMDset(void);
unsigned char GetTLEFault1(void);
unsigned char GetTLEFault2(void);
void TLE_Update(void);
void Task_TLE6232Process(void);

void Task_CANTXD_Process(void);
void CANTXD_MsgBufferUpdate(void);
void CANDownLoad(void);
void Task_FCUCMD_Process(void);


void Task_ErrorDiagnosisProcess(void);
int Set_ErrGrade(unsigned char ErrGrade);

extern unsigned int temp;
#endif /* TASKSCHEDULE_H_ */
