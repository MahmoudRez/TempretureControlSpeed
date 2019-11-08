/*
 * Timer_config.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*#include "std_types.h"*/
#include "MICRO_setting.h"

#define NA  0xFF
#define Timer2 1
// #define PWM_Half_cycle  128
// #define PWM_Quarter_cycle 64

/*typedef enum{
	Timer0,Timer1,Timer2,MAX_num_of_timers
}timer_type;*/

typedef enum{
	Dis_INT,EN_INT
}InT_timer;

typedef enum{
	Timer0,MAX_num_of_timers
}timer_type;

typedef enum{
	NO_clk,F_cpu_clk,F_cpu_8,F_cpu_64,F_cpu_256,F_cpu_1024,Exter_F_clk,Exter_R_clk
}timer_clk;

typedef enum{
	WG_Normal,WG_PWM_PHC,WG_CTC,WG_FPWM
}timer_WGMode;



// typedef enum{
// 	Normal,Toggle,Clear,Set
// }No_pwm;

// typedef enum{
// 	Clear_up_set_down=2,Set_up_clear_down
// }Phc_pwm;

// typedef enum{
// 	No_inverting_mode=2,Inverting_mode
// }F_pwm;

typedef enum{
	NPWM_Normal=0,
	NPWM_Toggle=1,
	NPWM_Clear=2,
	NPWM_Set=3,
	PHC_PWM_Clear_up_set_down=2,
	PHC_PWM_Set_up_clear_down=3, 
    FPWM_No_inverting_mode=2,
    FPWM_Inverting_mode=3,

}timer_COM;




typedef enum{
	Falling,Rising
}ICU_edges;


typedef struct{
	timer_clk clock;
	ICU_edges edge;
}ICU_config;

typedef struct{
    timer_type   T_type;
    InT_timer    T_INT;
	timer_clk    T_clk;
	timer_WGMode T_WGMode;
	uint8_t      ComVal;
	timer_COM    T_Compare_out_mode;
	
	//uint8_t      compare_val;
	//uint8_t      PWM_cycle;
	//ICU_config  ICU_conf;

}Timer_config;




void Clear_Timers(void);



extern Timer_config Timers_setup[MAX_num_of_timers];






#endif /* TIMER_CONFIG_H_ */
