/*
 *  Tmu.c
 *  Created on: Jan 11, 2020
 *  Author: Ahemd_Elbadwi
 */


/*************************************************************************/
/*                         Includes                                      */
/*************************************************************************/
#include "Tmu.h"
/*************************************************************************/
/*                         Defines                                       */
/*************************************************************************/
#define TIMER_MAX_COUNTS       (0xFF)
#define TIMER_PRESCALLER       (1024UL)
/*************************************************************************/
/*                         Typedefs                                      */
/*************************************************************************/
typedef struct str_TmuRequestCfg_t
{
	/* Required Delay : Periodicity in case of Periodic TMU Mode */
	uint16 u16_TmuDelayTime;
	/* each task(Function) has it's own counter counts till reach it's required Delay Time */
	uint16 u16_TmuTimerCounter;
	/* TMU Modes : One shot mode , Periodic mode */
	uint8 u8_TmuMode;
	/* Flag to shoe that is Task(Function) is added to TMU Buffer or not*/
	bool b_IsFunAddedToTmuBuffer;
	/* Desired Task(function) to be added to TMU buffer */
	Tmu_UserCbk_t Tmu_Usercbk;
}str_TmuRequestCfg_t;

/*************************************************************************/
/*                         Static Global Variables                       */
/*************************************************************************/
static ErrorStatus_t gErrorStatus_Tmu_Init;
static uint8 gu8_TmuResolution=ZERO_VALUE;
static str_TmuRequestCfg_t gastr_TmuBuffer[TMU_BUFFER_SIZE];
static uint8 gu8_TmuCurrentBufferSize=ZERO_VALUE;
static uint8 gu8_TimerPrelodValue=ZERO_VALUE;
static bool gb_TimerInterruptFlag=ZERO_VALUE;

/*************************************************************************/
/*                         CBF Definitions                               */
/*************************************************************************/

ErrorStatus_t Timer_Cbf(void)
{
	ErrorStatus_t ErrorStatus_timerCbf=E_OK;
	gb_TimerInterruptFlag =TRUE ;
	/* preload timer every beginning to achieve Tmu Resolution = 1msec */
	Timer_SetValue(Tmu_InitCfg.u8_TimerId,gu8_TimerPrelodValue);
	return ErrorStatus_timerCbf;
}

/*************************************************************************/
/*                         Apis's Definitions                            */
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
void Tmu_Init(void)
{
	ErrorStatus_t ErrorStatus_timer_Init=NOT_INITIALIZED_ERROR;
	gErrorStatus_Tmu_Init=(TMU_BASE_ERROR + NOT_INITIALIZED_ERROR);
	Timer_cfg_s Timer_cfg;
	gu8_TmuResolution=Tmu_InitCfg.u8_TimerRes;

	/***************** Configure Tmu Timer *************************/
	/* Set Timer Cbf */
	Timer_cfg.Timer_CBF=Timer_Cbf;
	Timer_cfg.Timer_CH_NO=Tmu_InitCfg.u8_TimerId;
	Timer_cfg.Timer_Mode=TIMER_MODE;
	Timer_cfg.Timer_Polling_Or_Interrupt=TIMER_INTERRUPT_MODE;
	/* prescaller 1024 as a low level design choice */
	Timer_cfg.Timer_Prescaler=TIMER_PRESCALER_1024;
	/***************** Tmu Timer Initialization ********************/
	ErrorStatus_timer_Init = Timer_Init(&Timer_cfg);

	if(SUCCESS == ErrorStatus_timer_Init)
	{
		gErrorStatus_Tmu_Init = (TMU_BASE_ERROR + SUCCESS);
	}
	else
	{
		gErrorStatus_Tmu_Init = (TMU_BASE_ERROR + NOT_INITIALIZED_ERROR);
	}
}

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

ErrorStatus_t Tmu_Start_Timer(uint8 TmuMode, uint16 TmuDelay , Tmu_UserCbk_t Tmu_UserFunctionToStartcbk)
{
	ErrorStatus_t ErrorStatus_tmuStart=NOT_DEFINED_ERROR;
	if(NULL != Tmu_UserFunctionToStartcbk)
	{

		/******** Resolution Range constrain : 1:16 msec *******/
		uint8 u8_TimerCounts=((F_CPU*Tmu_InitCfg.u8_TimerRes)/(TIMER_PRESCALLER*1000));

		gu8_TimerPrelodValue=(TIMER_MAX_COUNTS-u8_TimerCounts+1);
		static uint8 u8_TmuBufferIndex = ZERO_VALUE;
		/* Check if TMU is Success Initialized*/

		if(SUCCESS== (gErrorStatus_Tmu_Init - TMU_BASE_ERROR))
		{
			/* Check if TMU Buffer availability */
			if(u8_TmuBufferIndex < TMU_BUFFER_SIZE)
			{
				gastr_TmuBuffer[u8_TmuBufferIndex].u16_TmuTimerCounter=ZERO_VALUE;
				gastr_TmuBuffer[u8_TmuBufferIndex].u16_TmuDelayTime = TmuDelay;
				gastr_TmuBuffer[u8_TmuBufferIndex].u8_TmuMode = TmuMode;
				gastr_TmuBuffer[u8_TmuBufferIndex].Tmu_Usercbk = Tmu_UserFunctionToStartcbk;
				gastr_TmuBuffer[u8_TmuBufferIndex].b_IsFunAddedToTmuBuffer=TRUE;
				u8_TmuBufferIndex++;
				gu8_TmuCurrentBufferSize = u8_TmuBufferIndex;
				Timer_Start(Tmu_InitCfg.u8_TimerId,u8_TimerCounts);
				ErrorStatus_tmuStart=SUCCESS;
			}
			else
			{
				ErrorStatus_tmuStart = BUFFER_FULL_ERROR;

			}
		}
		else
		{
			ErrorStatus_tmuStart = NOT_INITIALIZED_ERROR;

		}
	}
	else
	{
		ErrorStatus_tmuStart=NULL_PTR_ERROR;
	}
	return (TMU_BASE_ERROR + ErrorStatus_tmuStart);
}


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

ErrorStatus_t Tmu_Stop_Timer(Tmu_UserCbk_t Tmu_UserFunctionToStopcbk)
{
	ErrorStatus_t ErrorStatus_tmu_Stop_Timer=NOT_DEFINED_ERROR;
	uint8 u8_Index=ZERO_VALUE ,u8_TmuBufferIterator;

	if(NULL != Tmu_UserFunctionToStopcbk)
	{
		/* loop till Find Index of Required function to stop in Tmu Buffer */
		for(u8_TmuBufferIterator=ZERO_VALUE;u8_TmuBufferIterator < gu8_TmuCurrentBufferSize;u8_TmuBufferIterator++)
		{
			if(gastr_TmuBuffer[u8_TmuBufferIterator].Tmu_Usercbk == Tmu_UserFunctionToStopcbk)
			{
				/* Check if The required function to Stop is actually added to the tmu buffer */
				if(TRUE == gastr_TmuBuffer[u8_TmuBufferIterator].b_IsFunAddedToTmuBuffer)
				{
					/* remove the required function to stop = Shift gastr_TmuBuffer and decrease gu8_TmuCurrentBufferSize by one */
					for(u8_Index=u8_TmuBufferIterator;u8_Index < gu8_TmuCurrentBufferSize;u8_Index++)
					{
						/* Stop the Timer if the Tmu buffer contains only one cell */
						if(gu8_TmuCurrentBufferSize == ONE_VALUE)
						{
							Timer_Stop(Tmu_InitCfg.u8_TimerId);
							break;
						}
						else
						{
							gastr_TmuBuffer[u8_Index].Tmu_Usercbk= gastr_TmuBuffer[u8_Index+1].Tmu_Usercbk;
							gastr_TmuBuffer[u8_Index].u16_TmuDelayTime=gastr_TmuBuffer[u8_Index+1].u16_TmuDelayTime;
							gastr_TmuBuffer[u8_Index].u16_TmuTimerCounter=gastr_TmuBuffer[u8_Index+1].u16_TmuTimerCounter;
							gastr_TmuBuffer[u8_Index].u8_TmuMode=gastr_TmuBuffer[u8_Index+1].u8_TmuMode;
							gastr_TmuBuffer[u8_Index].b_IsFunAddedToTmuBuffer=gastr_TmuBuffer[u8_Index+1].b_IsFunAddedToTmuBuffer;
						}
					}
					/* decrease gu8_TmuCurrentBufferSize by one */
					gu8_TmuCurrentBufferSize--;
					ErrorStatus_tmu_Stop_Timer=SUCCESS;
				}
				else
				{
					/* Do Nothing */
				}

			}
			else
			{
				/* Do Nothing */
			}
		}
	}
	else
	{
		ErrorStatus_tmu_Stop_Timer=NULL_PTR_ERROR;
	}

	return (TMU_BASE_ERROR + ErrorStatus_tmu_Stop_Timer);
}

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

void Tmu_Dispatcher(void)
{
	/* static uint16 u16_TmuTimerCounter=ZERO_VALUE; */
	uint8 Tmu_DispatcherIterrator;
	if(TRUE == gb_TimerInterruptFlag)
	{
		/* Reset Timer Interrupt Flag */
		gb_TimerInterruptFlag = FALSE;
		/* u16_TmuTimerCounter++; */
		for(Tmu_DispatcherIterrator=ZERO_VALUE;Tmu_DispatcherIterrator < gu8_TmuCurrentBufferSize;Tmu_DispatcherIterrator++)
		{
			/* Increment Buffer TMU Timer Counter of all Included Tasks*/
			gastr_TmuBuffer[Tmu_DispatcherIterrator].u16_TmuTimerCounter++;
			/* Check If TMU Timer Counter Reaches to the Required delay or not */
			if(gastr_TmuBuffer[Tmu_DispatcherIterrator].u16_TmuTimerCounter % gastr_TmuBuffer[Tmu_DispatcherIterrator].u16_TmuDelayTime == ZERO_VALUE)
			{
				/* Execute the APP. Function */
				gastr_TmuBuffer[Tmu_DispatcherIterrator].Tmu_Usercbk();

				/* check if this function is one shot ? */
				if(gastr_TmuBuffer[Tmu_DispatcherIterrator].u8_TmuMode == TMU_MODE_ONESHOT)
				{
					Tmu_Stop_Timer(gastr_TmuBuffer[Tmu_DispatcherIterrator].Tmu_Usercbk);
				}
				else
				{
					/* Do Nothing */
				}
			}
			else
			{
				/* Do Nothing */
			}
		}
	}
}


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


ErrorStatus_t Tmu_Deinit(void)
{
	ErrorStatus_t ErrorStatus_tmu_Deinit=SUCCESS;
	if(SUCCESS == gErrorStatus_Tmu_Init -TMU_BASE_ERROR)
	{
		/******* Deinit Timer Module *********/
		Timer_Deinit(Tmu_InitCfg.u8_TimerId);
		gErrorStatus_Tmu_Init=NOT_INITIALIZED_ERROR;
	}
	else
	{
		ErrorStatus_tmu_Deinit =DEINIT_ERROR;
	}

	return (ErrorStatus_tmu_Deinit + TMU_BASE_ERROR);

}
