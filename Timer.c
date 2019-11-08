
#include "Timers.h"
#define NULL_PTR    ((void*)0)
//#define  Timer0 5
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;


uint64 g_time_MS;

volatile uint8  g_tick = 0,g_tick2=0;

#define NUMBER_OF_OVERFLOWS_PER_HALF_SECOND 2



ISR(TIMER0_OVF_vect)
{
	
			
	if(g_callBackPtr != NULL_PTR)
	{
		
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


//ISR(TIMER0_COMP_vect)
// void ISR_TIMER0_COMP (void)
// {
// 
// 	if(g_callBackPtr2 != NULL_PTR)
// 	{
// 		/* Call the Call Back function in the application after the edge is detected */
// 		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
// 	}
// }

//ISR(TIMER2_OVF_vect)
void ISR_TIMER2_OVF (void)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


//ISR(TIMER2_COMP_vect)
// void ISR_TIMER2_COMP (void)
// {
// 
// 	if(g_callBackPtr2 != NULL_PTR)
// 	{
// 		/* Call the Call Back function in the application after the edge is detected */
// 		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
// 	}
// }



void timer_init(void )
{
	uint8 Loop_index=0;


	for(Loop_index=0;Loop_index<MAX_num_of_timers;Loop_index++)
	{
		switch(Timers_setup[Loop_index].T_type)
		{
		case Timer0:
			Clear_Timers(); //timer initial value

			TCCR0 = (1<<FOC0) | (Timers_setup[Loop_index].T_clk)|((Timers_setup[Loop_index].T_WGMode&0x02)<<2)
				    						|((Timers_setup[Loop_index].T_WGMode&0x01)<<6)|(Timers_setup[Loop_index].T_Compare_out_mode<<4);

			switch(Timers_setup[Loop_index].T_WGMode)   //enable overflow interrupt
			{
			case WG_Normal:
				if(Timers_setup[Loop_index].T_INT)
					TIMSK |= (1<<TOIE0);				 //En_TOF_interrupt of timer0

				break;
			case WG_CTC :
				if(Timers_setup[Loop_index].T_INT)
					TIMSK |= (1<<OCIE0);				//En_TCOM_interrupt of timer0

				OCR0 = Timers_setup[Loop_index].ComVal;

				break;
			case WG_FPWM :
				OCR0 = Timers_setup[Loop_index].ComVal;

				break;
			default:
				break;
			}




			break;

			/*case Timer1:

				   break;*/


			case Timer2:
				Clear_Timers(); //timer initial value

				TCCR2 = (1<<FOC2) | (Timers_setup[Loop_index].T_clk)|((Timers_setup[Loop_index].T_WGMode&0x02)<<2)
						|((Timers_setup[Loop_index].T_WGMode&0x01)<<6)|(Timers_setup[Loop_index].T_Compare_out_mode<<4);

				switch(Timers_setup[Loop_index].T_WGMode)   //enable overflow interrupt
				{
				case WG_Normal:
					//TIMSK |= (1<<TOIE2);
					if(Timers_setup[Loop_index].T_INT)
						TIMSK |= (1<<TOIE2);              //En_TOF_interrupt of timer0
					break;
				case WG_CTC :
					if(Timers_setup[Loop_index].T_INT)
						TIMSK |= (1<<OCIE2); //En_TCOM_interrupt of timer2

					OCR2 = Timers_setup[Loop_index].ComVal;

					break;
				case WG_FPWM :
					OCR2 = Timers_setup[Loop_index].ComVal;

					break;
				default:
					break;
				}


				break;

				//				case Timer1:

				default:
					break;


		}
	}
}




void Timer_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
void Timer_setCallBack2(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr2 = a_ptr;
}

void Toggle_Sec(void){


	g_tick2++;
	if(g_tick2 == 4)
	{
		PORTC = PORTC ^ (1<<PC1); //toggle led every 0.5 second
		//DIO_write(PORT_C,PIN0,Toggle);
		g_tick2 = 0; //clear the tick counter again to count a new 0.5 second
	}

}



void Toggle_half_sec(void){


	g_tick++;
	if(g_tick == NUMBER_OF_OVERFLOWS_PER_HALF_SECOND)
	{
		PORTC = PORTC ^ (1<<PC0); //toggle led every 0.5 second
		//DIO_write(PORT_C,PIN0,Toggle);
		g_tick = 0; //clear the tick counter again to count a new 0.5 second
	}

}

void Timer_Square_Wave_Init(void)
{



	uint8 loop_index=0;
	for(loop_index=0;loop_index<MAX_num_of_timers;loop_index++)
	{

		if(Timers_setup[loop_index].T_type==Timer0)
		{
			DDRB = DDRB | (1<<PB3);
		}
		if(Timers_setup[loop_index].T_type==Timer2)
		{
			DDRD = DDRD | (1<<PD7);
		}
	}



}

void Clear_Timers(void){
	uint8 loop_index=0;
	for(loop_index=0;loop_index<MAX_num_of_timers;loop_index++)
	{

		if(Timers_setup[loop_index].T_type==Timer0)
		{
			TCNT0 = 0;
		}
		if(Timers_setup[loop_index].T_type==Timer2)
		{
			TCNT2=0;
		}
	}


}

void Delay_ms(uint64 n_milleSec,t_type timer){
	if(timer==T0){

		TCNT0=131;
		TCCR0 = (1<<FOC0) | (1<<CS01) | (1<<CS00);
		while(n_milleSec){

			while( !(TIFR & (1<<TOV0) ) );
			TCNT0=131;
			n_milleSec--;
			TIFR |= (1<<TOV0);
		}

	}

	if(timer==T2){
		TCNT2=131;
		TCCR2 = (1<<FOC2) | (1<<CS21);
		while(n_milleSec){

			while( !(TIFR & (1<<TOV2) ) );
			TCNT0=131;
			n_milleSec--;
			TIFR |= (1<<TOV2);



		}
	}


// void Delay_ms(uint64_t n_milleSec,t_type timer){
// 	if(timer==T0){
// 
// 		TCNT0=131;
// 		TCCR0 = (1<<FOC0) | (1<<CS01) | (1<<CS00);
// 		while(n_milleSec){
// 
// 			while( !(TIFR & (1<<TOV0) ) );
// 			    TCNT0=131;
// 				n_milleSec--;
// 				TIFR |= (1<<TOV0);
// 		}
// 
// 	}
// 
// 	if(timer==T2){
// 		TCNT2=131;
// 		TCCR2 = (1<<FOC2) | (1<<CS21);
// 		while(n_milleSec){
// 
// 			while( !(TIFR & (1<<TOV2) ) );
// 			   TCNT0=131;
// 			   n_milleSec--;
// 			   TIFR |= (1<<TOV2);
// 
// 
// 
// 		}
// 	}

}

void Wait_ms(void){

	static uint64 count=0;
	static uint8 count4=0;
	count4++;

	if (31 == count4)
	{
		count++;
		count4 = 0;	

	}

	if(count == g_time_MS)
	{

		if(g_callBackPtr2 != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}

		count=0;

	}

}



void Dely_ms_service(t_type timer,uint64 time_MS,void(*ptr_display)(void))
{

	
    g_time_MS = time_MS;
	g_callBackPtr = Wait_ms;     //interrupt call

	g_callBackPtr2=ptr_display;             //func call
	
	

}







/*

void Dely_ms_service(t_type timer,void(*ptr_display)(void),void(*ptr_increment_time)(void),uint64_t time_MS)
{

    g_time_MS = time_MS;
	g_callBackPtr = ptr_increment_time;     //interrupt call

	g_callBackPtr2=ptr_display;             //func call
	if(timer==T0){

		TCNT0=131;
		TCCR0 = (1<<FOC0) | (1<<CS01);
		TIMSK |= (1<<TOIE0);



	}

*/


/*


	else if(timer==T2){
		uint8 count=0;
		TCNT2=131;
		TCCR2 = (1<<FOC0) | (1<<CS01);
		while(n_milleSec){
			while( !(TIFR & (1<<TOV2) ) );
			if(TIFR & (1<<TOV2) )
				count++;

			if(count==4)
			{
				n_milleSec--;
				count=0;

			}

		}
		if(g_callBackPtr2 != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected
			(*g_callBackPtr2)();  another method to call the function using pointer to function g_callBackPtr();
		}
	}
*/



void PWM(uint8 duty)
{
	OCR0=duty;
}

