/*
 * sensor.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */

#include"sensor.h"


/***********LM35 Temperature Sensor initialization***************/
/*
 * PROTOTYPE:void TempSensor_Init(uint8 channel_num);
 * I/P: uint8 as a conversion channel in Analog digital converter
 * o/p:   NULL
 * I-O/P: NULL
 * Return:NULL
 * */
void TempSensor_Init(ADC_Channel channel_num)
{
	/*Call Analog Digital Converter initialization function*/
	ADC_init(channel_num);
}

/***********LM35 Temperature Sensor Read***************/
/*
 * PROTOTYPE:uint16 TempSensor_Read(void);
 * I/P:   NULL
 * o/p:   NULL
 * I-O/P: NULL
 * Return:uint16 the value of tempreture after calculated from
 * 			Analog digital converter registers
 * */
uint16 TempSensor_Read(void)
{
	uint16 value=0,temp=0;
	/*Get the value of Analog digital converter registers*/
	value=ADC_read();
	/*convert the value of register to temperature*/
	temp=(150*value*5)/(1.5*1023);

	return temp;
}
