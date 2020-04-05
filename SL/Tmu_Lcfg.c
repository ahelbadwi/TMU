/*
 * Tmu_Lcfg.c
 *
 *  File Description : TMU Linking Configuration parameters
 *  Created on: Jan 11, 2020
 *  Author: Ahemd_Elbadwi
 */


/*************************************************************************/
/*                         Includes                                      */
/*************************************************************************/
#include "Tmu_Lcfg.h"

/*************************************************************************/
/*                         Linking Cfg                                   */
/*************************************************************************/
/* User Note: Range of Tmu Resolution is 1:16 msec */
Tmu_Cfg_s const Tmu_InitCfg =
{
.u8_TimerId=TMU_TIMER_ID,
.u8_TimerRes=TMU_TIMER_RESELOUTION_MSEC
};
