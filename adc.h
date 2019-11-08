/*
 * adc.h
 *
 * Created: 7/11/2019 2:28:28 AM
 *  Author: M_Moawad
 */ 

/* Done */

#ifndef ADC_H_
#define ADC_H_


/******** General configuration ***********/
#include <avr/io.h>
#include "STD_Types.h"
/*****************************************/


/*  ADC registers */

/***** Declare the generic ADMUX Register and its bits ******/
typedef struct{
	
	uint8 	MUX		 :5;			/* channel selection */
	uint8 	ADLAR_B  :1;			/* left adjustment result */
	uint8 	REFS 	 :2;			/* reference selection bits AREF BIT OR AVCC OR INTERNAL 2.65 */

}ADMUX_BFD;

#define ADMUX_BF (*((volatile ADMUX_BFD *) (& ADMUX)))
/****************************************************************/

/****** Declare the generic ADCSRA Register and its bits ********/
typedef struct{
	
	/* SINGLE BIT IS USED _B TO AVOID CONFLICT WITH IO LIBRARY OTHER WILL NOT */
	uint8 	ADPS	 :3;			/* prescaler select bits */
	uint8 	ADIE_B 	 :1;			/* interrupt enable */
	uint8 	ADIF_B 	 :1;			/* interrupt flag */
	uint8 	ADATE_B	 :1;			/* Auto Trigger Enable */
	uint8 	ADSC_B 	 :1;			/* start conversion  */
	uint8 	ADEN_B 	 :1;			/* ADC Driver Enable  */

}ADCSRA_BFD;

#define ADCSRA_BF (*((volatile ADCSRA_BFD *) (& ADCSRA)))
/**********************************************************/


/****** Declare the generic SFIOR Register and its bits ********/
typedef struct{
	
	/* SINGLE BIT IS USED _B TO AVOID CONFLICT WITH IO LIBRARY OTHER WILL NOT */
	uint8 	RESERVED_B 	 :5;			/* Reserved  */
	uint8 	ADTS_B 		 :3;			/* Auto Trigger Source  */

}SFIOR_BFD;

#define SFIOR_BF (*((volatile SFIOR_BFD *) (& SFIOR)))
/**********************************************************/

/************Maximum number of channels in ADC*************/
#define MAXChanel_NB (7)



/*************Analog Digital converter modes**********************/
#define NORMAL_MODE 0
#define AUTO_TRIGER 1
/***************Configure the ADC mode *****************/
#define MODE AUTO_TRIGER

/************  types of resolution*****************/
#define EIGHT_RESELOTION 1
#define TEN_RESELOTION 0
/************  Configure type of resolution*****************/
#define RESELOTION TEN_RESELOTION


/************Conversion Type  OF ADC***********/
#define ADC_INTERRUPT 1
#define ADC_POOLING 0
/************Configure type of Conversion ************/
#define CONVERSION_TYPE ADC_POOLING





/***************** Reference Voltages ********************/
#define 	ADC_REF_EXT	 0b00		/* Voltage on AREF*/
#define 	ADC_REF_5 	 0b01		/* Voltage on AVCC = 5V*/
#define 	ADC_REF_INT  0b11		/* Internal Voltage  = 2.65V*/
/******************Configure Refrence Voltage**************************/
#define V_REF ADC_REF_5

/********* clock prescaler division ********/
#define ADC_CLK_DIV_2      0b000	/* Dividing system frequency by 2 */
#define ADC_CLK_DIV_4      0b010	/* Dividing system frequency by 4 */
#define ADC_CLK_DIV_8      0b011	/* Dividing system frequency by 8 */
#define ADC_CLK_DIV_16     0b100	/* Dividing system frequency by 16 */
#define ADC_CLK_DIV_32     0b101	/* Dividing system frequency by 32 */
#define ADC_CLK_DIV_64     0b110	/* Dividing system frequency by 64 */
#define ADC_CLK_DIV_128    0b111	/* Dividing system frequency by 128 */
/*****************Configure Prescaler division*******************/
#define ADC_PRESCALER_DIVISION ADC_CLK_DIV_128

/***********************Channels of ADC*********************/
typedef enum {
	channel0,
	channel1,
	channel2,
	channel3,
	channel4,
	channel5,
	channel6,
	channel7
}ADC_Channel;


/*****************Auto Trigger Sources******************/
#define FREE_RUNNING 0
#define ANALOG_COMPARATOR 1
#define EXTERNAL_INTR0 2
#define TIMER_COUNTER0_CTC 3
#define TIMER_COUNTER0_OVF 4
#define TIMER_COUNTER_CTC_B 5
#define TIMER_COUNTER1_OVF 6
#define TIMER_COUNTER1_ICU 7
/***************Configure Auto_Triger_Source***********************/
#define AUTO_TRIGGER_SOURCE TIMER_COUNTER0_OVF


/******* ADC Functions prototypes **********/

/************** Initialize the adc driver *******************/
/*
 * PROTOTYPE:void ADC_init(uint8 channel);
 * I/P: Analog to digital Converter Channel
 * o/p: NULL
 * I-O/P:NULL
 * Return:NULL
 * */
extern void ADC_init(uint8 channel);

/************** Get the read from Analog Digital Converter driver *******************/
/*
 * PROTOTYPE:uint16  ADC_read(void);
 * I/P: NULL
 * o/p: NULL
 * I-O/P:NULL
 * Return:Analog digital converter reading as a short integer
 * variable
 * */
extern uint16  ADC_read(void);

/***********ADC Interrupt Prototype*********************/
/*
 * PROTOTYPE:void ADC_init(uint8 channel);
 * I/P: NULL
 * o/p: NULL
 * I-O/P:NULL
 * Return:NULL
 * */

void __vector__16(void ) __attribute__((signal,used,externally_visible));

/***********ADC Callback Prototype*********************/
/*
 * PROTOTYPE:void ADC_setCallBack(void(*ADC_ptr)(void));
 * I/P: NULL
 * o/p: a pointer to function calls when interrupt occurred
 * I-O/P:NULL
 * Return:NULL
 * */
extern void ADC_setCallBack(void(*ADC_ptr)(void));
#endif /* ADC_H_ */
