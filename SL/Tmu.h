/*
 * Tmu.h
 *
 *  Created on: Jan 11, 2020
 *      Author: Ahemd_Elbadwi 
 */

#ifndef TMU_H_
#define TMU_H_

/*************************************************************************/
/*                         Includes                                      */
/*************************************************************************/
#include "std_types.h"
#include "Utils.h"
#include "General_Macros.h"
#include "Retval.h"
#include "Tmu_Cfg.h"
#include "Tmu_Lcfg.h"

/*************************************************************************/
/*                         Defines                                       */
/*************************************************************************/
#define TMU_MODE_PERIODIC      (0U)
#define TMU_MODE_ONESHOT       (1U)
/*************************************************************************/
/*                         Typedef                                       */
/*************************************************************************/
typedef ErrorStatus_t (*Tmu_UserCbk_t) (void);
typedef ErrorStatus_t (*Tmu_TimerCbk_t) (void);

/*************************************************************************/
/*                         Apis's Exports                                */
/*************************************************************************/

/*******************************************************************************
 * 	Function name: 		TMU_Init
 *
 * 	Brief: 				initialize TMU module
 *
 * 	Details: 			initialize TMU module and
 *
 * 	Arguments:
 * 		-				NA
 *
 * 	Return:
 * 		-				ERROR_STATUS to report success or failure
 *******************************************************************************/
extern void Tmu_Init(void);
/*******************************************************************************
 * 	Function name: 		TMU_Start_time
 *
 * 	Brief: 				Starts a delay service in TMU
 *
 * 	Details: 			Starts a task to notify the user after a specific
 *						delay period
 *
 * 	Arguments:
 * 		-				pFun_FunctionToStart pointer to func to notify the user
 * 		-				TmuDelay: Function Periodicity
 * 		-				TmuMode : One Shot , Periodic
 *
 * 	Return:
 * 		-				the index of the task created
 *******************************************************************************/
extern ErrorStatus_t Tmu_Start_Timer(uint8 TmuMode, uint16 TmuDelay , ErrorStatus_t (*pFun_FunctionToStart) (void));
/*******************************************************************************
 * 	Function name: 		TMU_Stop_Time
 *
 * 	Brief: 				Remove Task (Function) From Tmu Buffer
 *
 * 	Details: 			stops a task to notify the user after a specific
 *						delay period
 *
 * 	Arguments:
 * 		-				pFunToStop: Function to be deleted

 *
 * 	Return:
 * 		-				return success or failure
 *******************************************************************************/

extern ErrorStatus_t Tmu_Stop_Timer(ErrorStatus_t (*pFunToStop) (void));

/*******************************************************************************
 * 	Function name: 		TMU_Dispatcher
 *
 * 	Brief: 				dispatcher TMU module
 *
 * 	Details: 			dispatches delay services that are due in TMU module
 *						and notify the user using the pointers to functions
 *						stored in its array
 *
 * 	Arguments:
 * 		-				void
 *
 * 	Return:
 * 		-				ERROR_STATUS to report success or failure
 *******************************************************************************/
extern void Tmu_Dispatcher(void);

/*******************************************************************************
 * 	Function name: 		TMU_DeInit
 *
 * 	Brief: 				De-initialize TMU module
 *
 * 	Details: 			De-initialize TMU module and
 *
 * 	Arguments:          NA
 *
 * 	Return:
 * 		-				ERROR_STATUS to report success or failure
 *******************************************************************************/

extern ErrorStatus_t Tmu_Deinit(void);

#endif /* TMU_H_ */
