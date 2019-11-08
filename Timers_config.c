/*
 * Timers_config.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */


#include "Timer_config.h"




Timer_config Timers_setup[MAX_num_of_timers]=
{
		{Timer0,EN_INT,F_cpu_1024,WG_Normal,0,NPWM_Normal}
		//{Timer2,EN_INT,F_cpu_clk,WG_FPWM,0,NPWM_Normal}
		//{Timer2,EN_INT,F_cpu_clk,WG_FPWM,Normal}
};




