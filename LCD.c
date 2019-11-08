
#define F_CPU 8000000ul
#include "LCD.h"
#include <util/delay.h>

static void LCD_sendCommand(uint8 CMND)
{
	DIO_Write(RS , LOW);
	DIO_Write(RW , LOW);

	DIO_Write(LCD_D4 , (CMND >> 4) &1);
	DIO_Write(LCD_D5 , (CMND >> 5) &1);
	DIO_Write(LCD_D6 , (CMND >> 6) &1);
	DIO_Write(LCD_D7 , (CMND >> 7) &1);

	DIO_Write( LCD_EN , HIGH);
	_delay_us(500);
	//CMD_PORT&=~(1<<EN);
	DIO_Write(LCD_EN , LOW);

	DIO_Write(LCD_D4 , (CMND >> 0) &1);
	DIO_Write(LCD_D5 , (CMND >> 1) &1);
	DIO_Write(LCD_D6 , (CMND >> 2) &1);
	DIO_Write(LCD_D7 , (CMND >> 3) &1);

	DIO_Write( LCD_EN , HIGH);
	_delay_us(500);
	//CMD_PORT&=~(1<<EN);
	DIO_Write(LCD_EN , LOW);

}


void LCD_DataWr(uint8 Data)
{
	DIO_Write(RS , HIGH);
	DIO_Write(RW , LOW);

	DIO_Write(LCD_D4 , (Data >> 4) &1 );
	DIO_Write(LCD_D5 , (Data >> 5) &1 );
	DIO_Write(LCD_D6 , (Data >> 6) &1 );
	DIO_Write(LCD_D7 , (Data >> 7) &1 );

	DIO_Write( LCD_EN , HIGH);
	_delay_us(500);
	//CMD_PORT&=~(1<<EN);
	DIO_Write(LCD_EN , LOW);

	DIO_Write(LCD_D4 , (Data >> 0) &1);
	DIO_Write(LCD_D5 , (Data >> 1) &1);
	DIO_Write(LCD_D6 , (Data >> 2) &1);
	DIO_Write(LCD_D7 , (Data >> 3) &1);

	DIO_Write( LCD_EN , HIGH);
	_delay_us(500);
	//CMD_PORT&=~(1<<EN);
	DIO_Write(LCD_EN , LOW);

}




void LCD_init(void){	DIO_Init();
	LCD_sendCommand(LCD_CursorHome);

	_delay_ms(1);
	LCD_sendCommand(LCD_Set4Bit2Lin);

	_delay_ms(1);
	LCD_sendCommand(LCD_DisOnCurOnBliOff);

	_delay_ms(1);
	LCD_sendCommand(LCD_IncOnShiOff);

	_delay_ms(1);
	LCD_sendCommand(LCD_ClearScreen);}void LCD_displayString(uint8 *COPY_ptrString){	uint8 local_iterator = 0;	while(COPY_ptrString[local_iterator])	{		LCD_DataWr(COPY_ptrString[local_iterator]);		local_iterator++;	}}void LCD_displayStringRowColumn(uint8 *COPY_ptrString,uint8 COPY_Row,uint8 COPY_Column){	LCD_gotoRowColumn(COPY_Row,COPY_Column);	uint8 local_iterator = 0;	while(COPY_ptrString[local_iterator])	{		LCD_DataWr(COPY_ptrString[local_iterator]);		local_iterator++;	}}void LCD_gotoRowColumn( uint8 COPY_u8Row , uint8 COPY_u8Column){	LCD_sendCommand((0x80)|(COPY_u8Column+(0x40*COPY_u8Row)));}void LCD_NUM_DISP(uint8 COPY_u8Row , uint8 COPY_u8Column, uint16 COPY_u16num)
{
	LCD_gotoRowColumn(COPY_u8Row,COPY_u8Column);
	if (0<=COPY_u16num)
	{
		if (COPY_u16num<=9) LCD_DataWr(COPY_u16num+0x30);
		else if(COPY_u16num<=99)
		{
			LCD_DataWr((COPY_u16num/10)+0x30);
			LCD_DataWr((COPY_u16num%10)+0x30);
		}
		else if(COPY_u16num<=999)
		{
			LCD_DataWr((COPY_u16num/100)+0x30);
			LCD_DataWr(((COPY_u16num/10)%10)+0x30);
			LCD_DataWr((COPY_u16num%10)+0x30);
		}
		else if (COPY_u16num<=9999)
		{
			LCD_DataWr((COPY_u16num/1000)+0x30);
			LCD_DataWr(((COPY_u16num/100)%10)+0x30);
			LCD_DataWr(((COPY_u16num/10)%10)+0x30);
			LCD_DataWr((COPY_u16num%10)+0x30);
		}
		else if (COPY_u16num<=99999)
		{
			LCD_DataWr((COPY_u16num/10000)+0x30);
			LCD_DataWr(((COPY_u16num/1000)%10)+0x30);
			LCD_DataWr(((COPY_u16num/100)%10)+0x30);
			LCD_DataWr(((COPY_u16num/10)%10)+0x30);
			LCD_DataWr((COPY_u16num%10)+0x30);
		}
	}

	if (0>COPY_u16num)
	{
		COPY_u16num = -1*COPY_u16num;

		if (COPY_u16num<=9)
		{
			LCD_DataWr(0x2d);
			LCD_DataWr(COPY_u16num+0x30);
		}
		else if(COPY_u16num<=99)
		{
			LCD_DataWr(0x2d);
			LCD_DataWr((COPY_u16num/10)+0x30);
			LCD_DataWr((COPY_u16num%10)+0x30);
		}
		else if(COPY_u16num<=999)
		{
			LCD_DataWr(0x2d);
			LCD_DataWr((COPY_u16num/100)+0x30);
			LCD_DataWr(((COPY_u16num/10)%10)+0x30);
			LCD_DataWr((COPY_u16num%10)+0x30);
		}

	}

}
