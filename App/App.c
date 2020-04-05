/*
 *  App.c
 *  Layer : App Layer
 *  Created on: Jan 12, 2020
 *  Author: Ahemd_Elbadwi
 *  Description: This File Contains Test Application that Toggles three LEDs ,
 *               The First One Toggle Each 50msec , The Second one Toggles Each 100msec
 *               and the Third One Toggles Each 150msec.
 *
 */

/*************************************************************************/
/*                         Includes                                      */
/*************************************************************************/
#include "App.h"
/*************************************************************************/
/*                         Static Global Variables                       */
/*************************************************************************/

static ErrorStatus_t gErrorStatus_AppInit;

/*************************************************************************/
/*                         Tmu Cbk Definitions                           */
/*************************************************************************/
ErrorStatus_t Tmu_Task0Cbf(void)
{
	ErrorStatus_t ErrorStatus_task0=NOT_INITIALIZED_ERROR , ERROR_STATUS_LED0Toggle=DIO_ERROR ;

	ERROR_STATUS_LED0Toggle= DIO_Toggle(LED_0_GPIO,LED_0_PIN);
	if((SUCCESS == gErrorStatus_AppInit - TMU_BASE_ERROR) && (DIO_ERROR ==ERROR_STATUS_LED0Toggle ))
	{
		ErrorStatus_task0 =SUCCESS;
	}
	else
	{
		/* Do Nothing */
	}
	return (TMU_BASE_ERROR+ ErrorStatus_task0);
}

ErrorStatus_t Tmu_Task1Cbf(void)
{
	ErrorStatus_t ErrorStatus_task1=NOT_INITIALIZED_ERROR , ERROR_STATUS_LED1Toggle=DIO_ERROR ;

	ERROR_STATUS_LED1Toggle= DIO_Toggle(LED_1_GPIO,LED_1_PIN);
	if((SUCCESS == gErrorStatus_AppInit - TMU_BASE_ERROR) && (DIO_ERROR ==ERROR_STATUS_LED1Toggle ))
	{
		ErrorStatus_task1 =SUCCESS;
	}
	else
	{
		/* Do Nothing */
	}
	return (TMU_BASE_ERROR + ErrorStatus_task1);
}

ErrorStatus_t Tmu_Task2Cbf(void)
{
	ErrorStatus_t ErrorStatus_task1=E_NOK , ERROR_STATUS_LED2Toggle=E_NOK ;

	ERROR_STATUS_LED2Toggle= DIO_Toggle(LED_2_GPIO,LED_2_PIN);
	if((SUCCESS == gErrorStatus_AppInit - TMU_BASE_ERROR) && (DIO_ERROR ==ERROR_STATUS_LED2Toggle ))
	{
		ErrorStatus_task1 =SUCCESS;
	}
	else
	{
		/* Do Nothing */
	}
	return (TMU_BASE_ERROR + ErrorStatus_task1);
}

/*************************************************************************/
/*                         Api.s's Definitions                           */
/*************************************************************************/

void App_Init(void)
{
	gErrorStatus_AppInit=(TMU_BASE_ERROR + SUCCESS);
	DIO_Cfg_s DIO_InitCfg;
	DIO_InitCfg.GPIO=LED_GPIO;
	DIO_InitCfg.dir=OUTPUT;
	DIO_InitCfg.pins=LED_0_PIN | LED_1_PIN | LED_2_PIN;
	DIO_init(&DIO_InitCfg);
	/**************** Tmu Initialization ********************/
	Tmu_Init();
	/************ Tasks insertion in Tmu Buffer *************/
	/********************* Task0 Insertion ******************/
	Tmu_Start_Timer(TMU_MODE_PERIODIC,TASK0_DELAY,Tmu_Task0Cbf);
	/********************* Task1 Insertion *******************/
	Tmu_Start_Timer(TMU_MODE_PERIODIC,TASK1_DELAY,Tmu_Task1Cbf);
	/********************* Task2 Insertion *******************/
	Tmu_Start_Timer(TMU_MODE_PERIODIC,TASK2_DELAY,Tmu_Task2Cbf);
}


