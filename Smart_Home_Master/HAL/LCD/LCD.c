
/* 
 * File    : LCD.c
 * Author  : Ammar.Yasser
 * SWC     : DIO
 * Version : V1
 * Created on Sunday : 20,8,2023 
 */

#include <avr/io.h>
#include "../../LIB/Bit_math.h"
#include "../../LIB/data_types.h"
#include "../../MCAL/DIO/DIO.h"
#include "LCD.h"
#include <util/delay.h>

static void LCD_voidSetCursor(u8 Copy_u8Row,u8 Copy_u8Coulmn);
static void LCD_voidSendEnable(void);
static void LCD_voidSend4Bit(u8 Copy_u8CommandData);
static void LCD_4Bit_voidSetCursor(u8 Copy_u8Row,u8 Copy_u8Coulmn);

void LCD_voidSendCommand(u8 Copy_u8Command)
{
	DIO_voidSetPinvalue(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_LOW);	
	DIO_voidSetPinvalue(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_LOW);
	
	DIO_voidSetPortvalue(LCD_DATA_PORT,Copy_u8Command);
	
	LCD_voidSendEnable();
}


void LCD_voidSendData(u8 Copy_u8Data)
{
	DIO_voidSetPinvalue(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_HIGH);	
	DIO_voidSetPinvalue(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_LOW);
	
	DIO_voidSetPortvalue(LCD_DATA_PORT,Copy_u8Data);
	
	LCD_voidSendEnable();
}
void LCD_voidSendDataPos(u8 Copy_u8Data,u8 Copy_u8Row,u8 Copy_u8Coulmn)
{
	LCD_voidSetCursor(Copy_u8Row,Copy_u8Coulmn);

	LCD_voidSendData(Copy_u8Data);
}

void LCD_8BitvoidInit(void)
{
	DIO_voidSetPortDirection(LCD_DATA_PORT,0xFF);
	
	DIO_voidSetPinDirection(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT,LCD_EN_PIN,DIO_OUTPUT);
	
	_delay_ms(35);
	
	LCD_voidSendCommand(LCD_8BIT_FUNC_SET);
	
	_delay_us(50);
	
	LCD_voidSendCommand(LCD_DISBLAY_ON_OFF);
	
	_delay_us(50);
	
	LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
	
	_delay_ms(5);
	


}

void LCD_voidSendString(u8 *Copy_PAString)
{


	for(u8 i=0;Copy_PAString[i];i++)
	{
		LCD_voidSendData(Copy_PAString[i]);
	}
}

void LCD_voidSendStringPos(u8 *Copy_PAString,u8 Copy_u8Row,u8 Copy_u8Coulmn)
{
	LCD_voidSetCursor(Copy_u8Row,Copy_u8Coulmn);

	for(u8 i=0;Copy_PAString[i];i++)
	{
		LCD_voidSendData(Copy_PAString[i]);
	}
}

void LCD_voidSendNumberPos(u32 Copy_u32number,u8 Copy_u8Row,u8 Copy_u8Coulmn)
{
	u8 num[11] = {0};

	sprintf(num,"%i",Copy_u32number);

	LCD_voidSendStringPos(num,Copy_u8Row,Copy_u8Coulmn);


}

void LCD_voidDrawCustomeCharPos(u8 *Copy_u8PAChar,u8 Copy_u8CharAddress,u8 Copy_u8Row,u8 Copy_u8Coulmn)
{
	LCD_voidSendCommand(LCD_CGRAM_START + (Copy_u8CharAddress*8));
	_delay_us(50);

	for(u8 i=0;i<8;i++)
	{
		LCD_voidSendData(Copy_u8PAChar[i]);
	}
	LCD_voidSendDataPos(Copy_u8CharAddress,Copy_u8Row,Copy_u8Coulmn);
}




void LCD_4BitvoidInit(void)
{
	DIO_voidSetPinDirection(LCD_DATA_PORT,DIO_PIN0,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_DATA_PORT,DIO_PIN1,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_DATA_PORT,DIO_PIN2,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_DATA_PORT,DIO_PIN3,DIO_OUTPUT);

	DIO_voidSetPinDirection(LCD_CONTROL_PORT,DIO_PIN0,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT,DIO_PIN1,DIO_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT,DIO_PIN2,DIO_OUTPUT);

	 _delay_ms(20);
	 LCD_4Bit_voidSendCommand(LCD_8BIT_FUNC_SET);
	 _delay_ms(5);
	 LCD_4Bit_voidSendCommand(LCD_8BIT_FUNC_SET);
	 _delay_us(150);
	 LCD_4Bit_voidSendCommand(LCD_8BIT_FUNC_SET);
	 LCD_4Bit_voidSendCommand(LCD_CLEAR_DISBLAY);
	 LCD_4Bit_voidSendCommand(LCD_RETURN_HOME);
	 LCD_4Bit_voidSendCommand(LCD_ENTERY_MODE);
	 LCD_4Bit_voidSendCommand(LCD_DISBLAY_ON_OFF);
	 LCD_4Bit_voidSendCommand(LCD_4BIT_FUNC_SET);
	 LCD_4Bit_voidSendCommand(DDRAM_START);



}



void LCD_4Bit_voidSendCommand(u8 Copy_u8Command)
{
	DIO_voidSetPinvalue(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_LOW);
	DIO_voidSetPinvalue(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_LOW);

	LCD_voidSend4Bit(Copy_u8Command>>4);
	LCD_voidSendEnable();
	LCD_voidSend4Bit(Copy_u8Command);
	LCD_voidSendEnable();

}

void LCD_4Bit_voidSendData(u8 Copy_u8Data)
{
	DIO_voidSetPinvalue(LCD_CONTROL_PORT,LCD_RS_PIN,DIO_HIGH);
	DIO_voidSetPinvalue(LCD_CONTROL_PORT,LCD_RW_PIN,DIO_LOW);

	LCD_voidSend4Bit(Copy_u8Data>>4);
	LCD_voidSendEnable();
	LCD_voidSend4Bit(Copy_u8Data);
	LCD_voidSendEnable();

}

void LCD_4Bit_voidSendDataPos(u8 Copy_u8Data,u8 Copy_u8Row,u8 Copy_u8Coulmn)
{
	LCD_4Bit_voidSetCursor(Copy_u8Row,Copy_u8Coulmn);
	LCD_4Bit_voidSendData(Copy_u8Data);

}

void LCD_4Bit_voidSendString(u8 *Copy_PAString)
{


	for(u8 i=0;Copy_PAString[i];i++)
	{
		LCD_4Bit_voidSendData(Copy_PAString[i]);
	}
}

void LCD_4Bit_voidSendStringPos(u8 *Copy_PAString,u8 Copy_u8Row,u8 Copy_u8Coulmn)
{
	LCD_4Bit_voidSetCursor(Copy_u8Row,Copy_u8Coulmn);

	for(u8 i=0;Copy_PAString[i];i++)
	{
		LCD_4Bit_voidSendData(Copy_PAString[i]);
	}
}


void LCD_4Bit_voidSendNumberPos(u32 Copy_u32number,u8 Copy_u8Row,u8 Copy_u8Coulmn)
{
	u8 num[11] = {0};

	sprintf(num,"%i",Copy_u32number);

	LCD_4Bit_voidSendStringPos(num,Copy_u8Row,Copy_u8Coulmn);


}

void LCD_4Bit_voidDrawCustomeCharPos(u8 *Copy_u8PAChar,u8 Copy_u8CharAddress,u8 Copy_u8Row,u8 Copy_u8Coulmn)
{
	LCD_4Bit_voidSendCommand(LCD_CGRAM_START + (Copy_u8CharAddress*8));
	_delay_us(50);

	for(u8 i=0;i<8;i++)
	{
		LCD_4Bit_voidSendData(Copy_u8PAChar[i]);
	}
	LCD_4Bit_voidSendDataPos(Copy_u8CharAddress,Copy_u8Row,Copy_u8Coulmn);
}

static void LCD_voidSend4Bit(u8 Copy_u8CommandData)
{
	DIO_voidSetPinvalue(LCD_DATA_PORT,DIO_PIN0,(Copy_u8CommandData>>0)&(u8)0x01);
	DIO_voidSetPinvalue(LCD_DATA_PORT,DIO_PIN1,(Copy_u8CommandData>>1)&(u8)0x01);
	DIO_voidSetPinvalue(LCD_DATA_PORT,DIO_PIN2,(Copy_u8CommandData>>2)&(u8)0x01);
	DIO_voidSetPinvalue(LCD_DATA_PORT,DIO_PIN3,(Copy_u8CommandData>>3)&(u8)0x01);
}

static void LCD_voidSendEnable(void)
{
	DIO_voidSetPinvalue(LCD_CONTROL_PORT,LCD_EN_PIN,DIO_HIGH);
	_delay_ms(1);
	DIO_voidSetPinvalue(LCD_CONTROL_PORT,LCD_EN_PIN,DIO_LOW);

}

static void LCD_voidSetCursor(u8 Copy_u8Row,u8 Copy_u8Coulmn)
{
	Copy_u8Coulmn--;
	switch(Copy_u8Row)
	{

		case ROW1:

			LCD_voidSendCommand(0x80+Copy_u8Coulmn);

		break;
		case ROW2:

			LCD_voidSendCommand(0xC0+Copy_u8Coulmn);
		break;
		case ROW3:

			LCD_voidSendCommand(0x94+Copy_u8Coulmn);

		break;
		case ROW4:

			LCD_voidSendCommand(0xD4+Copy_u8Coulmn);
		break;
	}
}

static void LCD_4Bit_voidSetCursor(u8 Copy_u8Row,u8 Copy_u8Coulmn)
{
	Copy_u8Coulmn--;
	switch(Copy_u8Row)
	{

		case ROW1:

			LCD_4Bit_voidSendCommand(0x80+Copy_u8Coulmn);

		break;
		case ROW2:

			LCD_4Bit_voidSendCommand(0xC0+Copy_u8Coulmn);
		break;
	}
}


