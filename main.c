/***************************************************************************
 *  File name : main.c
 *  Created on: Jan 14, 2020
 *  Author: Ahemd_Elbadwi
 *  Description: main System Application that Toggles three LEDs ,
 *               The First One Toggle Each 50msec , The Second one
 *               Toggles Each 100msec and the Third One Toggles
 *               Each 150msec.
 *************************************************************************/

/*************************************************************************/
/*                         Includes                                      */
/*************************************************************************/
#include "App.h"
#include "sleep.h"

int main(void)
{
	/**** Test Application Initialization ****/
	App_Init();
	/**************** Super Loop *************/
	while(1)
	{
		Tmu_Dispatcher();
		CPU_Sleep(IDLE);
	}
	return 0;
}
