/*
 * sensor.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include"adc.h"

/***********LM35 Temperature Sensor initialization***************/
/*
 * PROTOTYPE:void TempSensor_Init(uint8 channel_num);
 * I/P: uint8 as a conversion channel in Analog digital converter
 * o/p:   NULL
 * I-O/P: NULL
 * Return:NULL
 * */
extern void TempSensor_Init(uint8 channel_num);
/***********LM35 Temperature Sensor Read***************/
/*
 * PROTOTYPE:uint16 TempSensor_Read(void);
 * I/P:   NULL
 * o/p:   NULL
 * I-O/P: NULL
 * Return:uint16 the value of tempreture after calculated from
 * 			Analog digital converter registers
 * */
extern uint16 TempSensor_Read(void);
#endif /* SENSOR_H_ */
