/*
 * Timers.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */

#ifndef TIMERS_H_
#define TIMERS_H_


#include "Timer_config.h"

typedef enum{
	T0,T2
}t_type;


extern void Delay_ms(uint64_t n_milleSec,t_type timer);

extern void Dely_ms_service(t_type timer,uint64_t time_MS,void(*ptr_display)(void));

extern void timer_init(void );
extern void Timer_Square_Wave_Init(void);

extern void Timer_setCallBack(void(*a_ptr)(void));

extern void Toggle_half_sec(void);


extern void Toggle_Sec(void);


extern void PWM(uint8_t duty);




#endif /* TIMERS_H_ */
