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
long AD_Lagrange(const unsigned int x[], const unsigned int y[], const int len, int xh);
void Task_TLE6232UpdateProcess(void);
void Task_TLE6232CMDsetProcess(void);
unsigned int TLE_SPI_SendCMD(unsigned char ControlByte, unsigned char DataByte ,unsigned int TLEType);
void Task_CANTXD_Process(void);
void CANTXD_MsgBufferUpdate(void);
void CANDownLoad(void);
void Task_FCUCMD_Process(void);
void Task_ErrorDiagnosisProcess(void);
int Set_ErrGrade(unsigned char ErrGrade);

extern unsigned int temp;
#endif /* TASKSCHEDULE_H_ */
