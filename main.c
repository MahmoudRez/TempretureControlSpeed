/*
 * ADC_Task.c
 *
 * Created: 11/7/2019 5:43:43 PM
 * Author : M_Moawad
 */ 

//#include <avr/io.h>

#define F_CPU 8000000ul
#include"sensor.h"
#include"Timers.h"
#include "LCD.h"

/************** Callback func for App *******************/
/*
 * PROTOTYPE:static void SetCallBack(void);
 * I/P:   NULL
 * o/p:   NULL
 * I-O/P: NULL
 * Return:NULL
 * */
static void SetCallBack(void);


/************** Global variables *******************/

static volatile uint8 g_SetCallBackFlag=0;
static uint8 g_DutyCycle=50;
static uint8 g_TempValue=0;


int main(void)
{
	static uint16 LOC_TempValue=0;
	LCD_init();
	TempSensor_Init(channel0);
	timer_init();
	Timer_setCallBack(SetCallBack);
	LCD_displayString("Welcome");
	SREG |= (1<<7);
	
	while (1)
	{
		if(1==g_SetCallBackFlag)
		{
			LOC_TempValue = TempSensor_Read();
			
			LCD_displayStringRowColumn("TEMP:  ",0,0);
			LCD_NUM_DISP(0,7,LOC_TempValue);
			LCD_displayStringRowColumn("Duty Cycle:",1,0);
		
		
		
			if(0<=LOC_TempValue<=27)
			{
				g_DutyCycle=50;
				g_TempValue=LOC_TempValue;
			}
			else if(LOC_TempValue==g_TempValue+2)
			{
				g_DutyCycle+=10;
				g_TempValue=LOC_TempValue;

			}
			else if(LOC_TempValue==g_TempValue-2)
			{
				g_DutyCycle-=10;
				g_TempValue=LOC_TempValue;
			}
			LCD_NUM_DISP(1,12,g_DutyCycle);
			g_SetCallBackFlag=0;
		}
		else
		{

		}
		
		
		
	}
}

/************** Callback func for App *******************/
/*
 * PROTOTYPE:static void SetCallBack(void);
 * I/P:   NULL
 * o/p:   NULL
 * I-O/P: NULL
 * Return:NULL
 * */

static void SetCallBack(void)
{
				
				
		if (g_SetCallBackFlag==0)
		{
			g_SetCallBackFlag=1;
		}
	

}
