/*
 * adc.c
 *
 * Created: 7/11/2019 2:28:41 AM
 *  Author: M_Moawad
 */ 

/* Done */

#include "adc.h"

static volatile void (*gADC_callBackPtr)(void) = NULL_PTR;
/***********ADC Callback Prototype*********************/
/*
 * PROTOTYPE:void ADC_setCallBack(void(*ADC_ptr)(void));
 * I/P: NULL
 * o/p: a pointer to function calls when interrupt occurred
 * I-O/P:NULL
 * Return:NULL
 * */
void ADC_setCallBack(void(*ADC_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	(gADC_callBackPtr) = (ADC_ptr);
}

/************** Initialize the ADC driver *******************/
/*
 * PROTOTYPE:void ADC_init(uint8 channel);
 * I/P: Analog to digital Converter Channel
 * o/p: NULL
 * I-O/P:NULL
 * Return:NULL
 * */
void ADC_init(uint8 channel)
{
	/*********** Check The Reference voltage ***********/
	switch(V_REF)
	{
	case ADC_REF_EXT:
		/**** configure Reference voltage as external voltage ****/
		ADMUX_BF.REFS = ADC_REF_EXT;
		break;
	case ADC_REF_5:
		/**** configure Reference voltage as 5 volt ****/
		ADMUX_BF.REFS = ADC_REF_5;
		break;
	case ADC_REF_INT:
		/**** configure Reference voltage as 2.65 volt ****/
		ADMUX_BF.REFS = ADC_REF_INT;

		break;
	}


	/************** Selecting ADC Channel ****************/
	if(MAXChanel_NB>=channel)
	{
		ADMUX_BF.MUX = channel ;
	}


	/************** Prescaler selection ******************/
	switch(ADC_PRESCALER_DIVISION)
	{
	case ADC_CLK_DIV_2:
		ADCSRA_BF.ADPS = ADC_CLK_DIV_2;
		break;
	case ADC_CLK_DIV_4:
		ADCSRA_BF.ADPS = ADC_CLK_DIV_4;
		break;
	case ADC_CLK_DIV_8:
		ADCSRA_BF.ADPS = ADC_CLK_DIV_8;
		break;
	case ADC_CLK_DIV_16:
		ADCSRA_BF.ADPS = ADC_CLK_DIV_16;
		break;
	case ADC_CLK_DIV_32:
		ADCSRA_BF.ADPS = ADC_CLK_DIV_32;
		break;
	case ADC_CLK_DIV_64:
		ADCSRA_BF.ADPS = ADC_CLK_DIV_64;
		break;
	case ADC_CLK_DIV_128:
		ADCSRA_BF.ADPS = ADC_CLK_DIV_128;
		break;
	}



#if (MODE==AUTO_TRIGER)
	/************ Auto Trigger Enable  ***************/
	ADCSRA_BF.ADATE_B = 1;



	/**********Check the source of trigger in case Auto trigger************/
	switch(AUTO_TRIGGER_SOURCE)
	{
	case FREE_RUNNING:
		/* Selecting auto trigger Source as afree running Source*/
		SFIOR_BF.ADTS_B = FREE_RUNNING;
		break;
	case ANALOG_COMPARATOR:
		/* Selecting auto trigger Source as an analog comparator*/
		SFIOR_BF.ADTS_B = ANALOG_COMPARATOR;
		break;
	case EXTERNAL_INTR0:
		/* Selecting auto trigger source as external interrupt 0 */
		SFIOR_BF.ADTS_B = EXTERNAL_INTR0;
		break;
	case TIMER_COUNTER0_CTC:
		/* Selecting auto trigger source as timer0 CTC Interrupt */
		SFIOR_BF.ADTS_B = TIMER_COUNTER0_CTC;
		break;
	case TIMER_COUNTER0_OVF:
		/* Selecting auto trigger source as timer0 OVF Interrupt */
		SFIOR_BF.ADTS_B = TIMER_COUNTER0_OVF;
		break;
	case TIMER_COUNTER_CTC_B:
		/***** Selecting auto trigger source as
		 * timer CTC Channel B Interrupt *******/
		SFIOR_BF.ADTS_B = TIMER_COUNTER_CTC_B;
		break;
	case TIMER_COUNTER1_OVF:
		/* Selecting auto trigger source as timer1 OVF Interrupt */
		SFIOR_BF.ADTS_B = TIMER_COUNTER1_OVF;
		break;
	case TIMER_COUNTER1_ICU:
		/* Selecting auto trigger source as
		 * timer1 Input Capture unit Interrupt */
		SFIOR_BF.ADTS_B = TIMER_COUNTER1_ICU;
		break;
	}
#endif

#if (ADC_POOLING==CONVERSION_TYPE)
	ADCSRA_BF.ADIE_B=ADC_POOLING;
#elif (ADC_INTERRUPT==CONVERSION_TYPE)
	ADCSRA_BF.ADIE_B=ADC_INTERRUPT;
#endif


	/************  Configure type of resolution*****************/
#if(EIGHT_RESELOTION==RESELOTION)
	/*******select Left Adjustment mode******/
	ADMUX_BF.ADLAR_B=EIGHT_RESELOTION;
#elif(TEN_RESELOTION==RESELOTION)
	/********select right Adjustment mode*****/
	ADMUX_BF.ADLAR_B=TEN_RESELOTION;
#endif



	/****************** Enable the ADC  ******************/
	ADCSRA_BF.ADEN_B = 1;

}
/************************************************************/


/***********Start ADC operation and conversion *************/
/************** Get the read from Analog Digital Converter driver *******************/
/*
 * PROTOTYPE:uint16  ADC_read(void);
 * I/P: NULL
 * o/p: NULL
 * I-O/P:NULL
 * Return:Analog digital converter reading as a short integer
 * variable
 * */
uint16 ADC_read(void){

	uint16 ADC_value;
	/*********Check the mode of ADC as normal or Auto trigger*********/
#if (MODE == NORMAL_MODE)
	{
#if(ADC_POOLING==CONVERSION_TYPE)
		/* START THE CONVERSION THEN HW WILL
		 *  CLEAR IT AFTER CONVERSION */
		ADCSRA_BF.ADSC_B = 1 ;
		/* Polling until the flag of conversion
		 * cleared by hard_ware after conversion   */
		while( ADCSRA_BF.ADSC_B == 0 );
		/*Read the value of ADC Register*/
		ADC_value = ADC;
#elif(ADC_INTERRUPT==CONVERSION_TYPE)
#endif

	}

#elif (MODE == AUTO_TRIGER)
#if (ADC_POOLING==CONVERSION_TYPE)
	/* Polling until the flag of conversion
	 * cleared by hard_ware after conversion   */
	while( ADCSRA_BF.ADSC_B == 0 );		
	/*Read the value of ADC Register*/
	ADC_value = ADC;
#elif(ADC_INTERRUPT==CONVERSION_TYPE)
#endif

#endif

	/* RETURN THE CONTENT OF THE 16-bit ADC DATA REGISTER */
	return ADC_value ;

}
/***********************************************************/
/***********ADC Interrupt Prototype*********************/
/*
 * PROTOTYPE:void ADC_init(uint8 channel);
 * I/P: NULL
 * o/p: NULL
 * I-O/P:NULL
 * Return:NULL
 * */
void __vector__16(void )
{
	if(gADC_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*gADC_callBackPtr)();
			/* another method to call the function using pointer to function g_callBackPtr(); */
		}
}
