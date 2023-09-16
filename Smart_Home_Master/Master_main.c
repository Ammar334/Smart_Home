/*
 * main.c
 *
 *  Created on: 2023/9/9
 *  Author: Ammar Yasser
 */

#include <avr/io.h>
#include <stdio.h>
#include "MCAL/DIO/DIO.h"
#include <util/delay.h>
#include "HAL/LCD/LCD.h"
#include <string.h>
#include <avr/interrupt.h>
#include "MCAL/ADC/ADC.h"
#include "MCAL/SPI/SPI.h"
#include "HAL/EEPROM/EEPROM.h"
#include "MCAL/I2C/I2C.h"
#include "LIB/Bit_math.h"
#include "LIB/data_types.h"
#include "HAL/KEYPAD/KEYPAD.h"



void Mode_1(u8 *Air_cound_Degree,u8 *l,u8 *chose);
void Mode_2(u8 *Heater_Degree,u8 *l,u8 *chose);
void Mode_3(u8 *l,u8 *chose,u8 *Heater_Degree,u8 *Air_cound_Degree,u16 *true_value);
void Mode_4(u8 *flag,u8 *chose);


int main(void)
{
	u8 value =0;
	u8 Pass_string[20]={0};
	u32 pass=0;
	u8 i=0;
	s8 tries =3;
	u8 flag=0;
	u8 chose=0;
	u8  Air_cound_Degree = 23;
	u8  Heater_Degree= 5;
	u16 digital_value=0;
	u16 analog_value=0;
	u16 true_value=0;

	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN7,DIO_OUTPUT);
	LCD_8BitvoidInit();
	KPD_voidInit();
	ADC_voidInit();
	SPI_voidInit();
	I2C_voidMasterInit();


	while(1)
	{
		digital_value = ADC_u16GetDigitalValue(ADC_CHANNEL7);
		analog_value = (digital_value * 5000UL)/255;
		true_value = (analog_value/40);
		if(EEPROM_voidReadData(0)!=0xFF)//Check if the pass is set
		{
			if(flag==0)
			{
				LCD_voidSendStringPos("Enter Password :",1,1);
				value = KPD_u8GetPressKey();
			}
			if((value == '=')||(flag>0))
			{
				pass = atoi(Pass_string);
				if((pass == EEPROM_voidReadData(0))||(flag>0))//Check if the pass is true
				{
					if(flag==0)
					{
						LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
						_delay_ms(50);
						LCD_voidSendStringPos("Welcome",1,7);
						_delay_ms(500);
						tries = 3;
						flag=1;
						LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
					}
					else
					{
						if(flag==1)
						{

							LCD_voidSendStringPos("1-Air Conditioner",1,1);
							LCD_voidSendStringPos("2-Heater",2,1);
							LCD_voidSendStringPos("3-Auto Use",3,1);
							LCD_voidSendStringPos("4-Rooms",4,1);
							LCD_voidSendStringPos("5-Exit",4,13);
							chose = KPD_u8GetPressKey();
						}
						SPI_u8Tranceive(chose);
						switch(chose)
						{
							case '1':
								Mode_1(&Air_cound_Degree,&flag,&chose);
								break;
							case '2':
								Mode_2(&Heater_Degree,&flag,&chose);
								break;
							case '3':
								Mode_3(&flag,&chose,&Heater_Degree,&Air_cound_Degree,&true_value);
								break;
							case '4':
								Mode_4(&flag,&chose);
								break;
							case '5':
								LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
								i=0;
								memset(Pass_string,'\0',20);
								flag=0;
								break;
							default :
								if(chose != KPD_CHECK_KEY)
								{
									LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
									LCD_voidSendStringPos("Invalid Chose ",1,1);
									_delay_ms(700);
								}
								break;
						}

					}

			}
			else
			{
				tries--;
				LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				_delay_ms(50);
				if(tries < 0)
				{
					LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
					LCD_voidSendStringPos("No More Tries",1,1);
					LCD_voidSendStringPos("Wait 20 Second",2,1);
					_delay_ms(20000);
				}
				else
				{
					LCD_voidSendStringPos("Wrong pass",1,6);
					LCD_voidSendNumberPos(tries,2,3);
					LCD_voidSendStringPos(" Tries Left",2,6);
					_delay_ms(800);
					LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				}

			}
			i=0;
			memset(Pass_string,'\0',20);
			}
			else if(value == 'c')
			{
				LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				i=0;
				memset(Pass_string,'\0',20);
			}
			else if(value != KPD_CHECK_KEY)
			{
				LCD_voidSendDataPos(value,2,(i+1));
				Pass_string[i] = value;
				_delay_ms(200);
				LCD_voidSendDataPos('*',2,(i+1));
				i++;
			}
		}
		else
		{
			LCD_voidSendStringPos("SET Password :",1,1);//set pass
			value = KPD_u8GetPressKey();
			if(value == '=')
			{
				i=0;
				pass = atoi (Pass_string);
				EEPROM_voidWriteData(pass,0);
				LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				memset(Pass_string,'\0',20);
			}
			else if(value != KPD_CHECK_KEY)
			{
				LCD_voidSendDataPos(value,2,(i+1));
				Pass_string[i] = value;
				_delay_ms(200);
				LCD_voidSendDataPos('*',2,(i+1));
				i++;
			}
		}
		if(true_value >55)
		{
			DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN7,DIO_HIGH);
		}
		else
		{
			DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN7,DIO_LOW);
		}
	}

	return 0;
}




void Mode_1(u8 *Air_cound_Degree,u8 *flag,u8 *chose)
{
	u8 v=0;
	if(*flag==1)
	{
		LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
	}
	*flag=2;
	LCD_voidSendStringPos("1-Lower the temp",1,1);
	LCD_voidSendStringPos("2-Raise the temp",2,1);
	LCD_voidSendStringPos("3-STOP ",3,1);
	LCD_voidSendStringPos("4-Back",4,1);
	LCD_voidSendNumberPos(*Air_cound_Degree,4,18);
	v = KPD_u8GetPressKey();
	SPI_u8Tranceive(v);
	switch(v)
	{
		case '1':
			if(*Air_cound_Degree<30)
			{
				(*Air_cound_Degree)++;
			}
			break;
		case '2':
			if(*Air_cound_Degree > 18)
			{
				(*Air_cound_Degree)--;
			}
			break;
		case '3':
			*Air_cound_Degree=30;
			break;
		case '4':
			LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
			*flag=1;
			*chose=KPD_CHECK_KEY;
			break;
		default :

			if(v != KPD_CHECK_KEY)
			{
				LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				LCD_voidSendStringPos("Invalid Chose ",4,1);
				_delay_ms(700);
			}
			break;

	}
}

void Mode_2(u8 *Heater_Degree,u8 *flag,u8 *chose)
{
	u8 v=0;
	if(*flag==1)
	{
		LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
	}
	if(*Heater_Degree<10)
	{
		LCD_voidSendDataPos(' ',4,19);
	}
	*flag=2;
	LCD_voidSendStringPos("1-Raise the temp",1,1);
	LCD_voidSendStringPos("2-Lower the temp",2,1);
	LCD_voidSendStringPos("3-STOP ",3,1);
	LCD_voidSendStringPos("4-Back",4,1);
	LCD_voidSendNumberPos(*Heater_Degree,4,18);
	v = KPD_u8GetPressKey();
	SPI_u8Tranceive(v);
	switch(v)
	{
		case '1':
			if(*Heater_Degree < 10)
			{
				(*Heater_Degree)++;
			}
			break;
			case '2':
			if(*Heater_Degree > 0)
			{
				(*Heater_Degree)--;
			}
			break;
		case '3':
			*Heater_Degree = 0;
			LCD_voidSendDataPos(' ',4,19);
			break;
		case '4':
			LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
			*flag=1;
			*chose=KPD_CHECK_KEY;
			break;
		default :
			if(v != KPD_CHECK_KEY)
			{
				LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				LCD_voidSendStringPos("Invalid Chose ",4,1);
				_delay_ms(700);
			}
	}
}

void Mode_3(u8 *flag,u8 *chose,u8 *Heater_Degree,u8 *Air_cound_Degree,u16 *true_value)
{

	u8 v=0;

	if(*flag==1)
	{
		LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
	}
	*flag=2;
	if(*true_value <10)
	{
		LCD_voidSendDataPos(' ',1,16);
	}

	LCD_voidSendStringPos("Temperature : ",1,1);
	LCD_voidSendNumberPos(*true_value,1,15);
	LCD_voidSendStringPos("2-Back",4,1);
	v = KPD_u8GetPressKey();
	SPI_u8Tranceive(*true_value);
	if(*true_value <=5)
	{
		*Heater_Degree = 10;
	}
	else if(*true_value <10)
	{
		*Heater_Degree = 8;
	}
	else if(*true_value <16)
	{
		*Heater_Degree = 6;
	}
	else if(*true_value <=20)
	{
		*Heater_Degree = 3;
		*Air_cound_Degree = 29;
	}
	else if(*true_value <=23)
	{
		*Heater_Degree = 0;
		*Air_cound_Degree = 29;
	}
	else if((*true_value >23)&&(*true_value <30))
	{
		*Air_cound_Degree = 26;
		*Heater_Degree = 18;
	}
	else if ((*true_value <35)&&(*true_value >=30))
	{
		*Air_cound_Degree = 24;
	}
	else if((*true_value <40)&&(*true_value >=35))
	{
		*Air_cound_Degree = 22;
	}
	else if(*true_value >=40)
	{
		*Air_cound_Degree = 18;
	}
	if(v == '2')
	{
		LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
		*flag=1;
		*chose=KPD_CHECK_KEY;
	}
	else if(v != KPD_CHECK_KEY)
	{
		LCD_voidSendStringPos("Invalid Chose",3,4);
		_delay_ms(800);
		LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
	}
}

void Mode_4(u8 *flag,u8 *chose)
{
	static u8 room =0;
	static u8 room_state=0;
	if(*flag==1)
	{
		*flag=2;
	}
	if(*flag==2)
	{
		*flag=3;
		LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
	}
	if(*flag==3)
	{
		LCD_voidSendStringPos("1-Room 1",1,1);
		LCD_voidSendStringPos("2-Room 2",2,1);
		LCD_voidSendStringPos("3-Room 3",3,1);
		LCD_voidSendStringPos("4-Room 4",4,1);
		LCD_voidSendStringPos("5-Back",4,10);
		room = KPD_u8GetPressKey();
	}
	SPI_u8Tranceive(room);
	switch(room)
	{
		case '1':
			if(*flag==3)
			{
				*flag=4;
				LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				LCD_voidSendStringPos("1-Turn On",1,1);
				LCD_voidSendStringPos("2-Turn Off",2,1);
				LCD_voidSendStringPos("3-Back",3,1);
			}
			room_state = KPD_u8GetPressKey();
			if(room_state == '3')
			{
				*flag=2;

			}
			SPI_u8Tranceive(room_state);
			break;
		case '2':
			if(*flag==3)
			{
				*flag=4;
				LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				LCD_voidSendStringPos("1-Turn On",1,1);
				LCD_voidSendStringPos("2-Turn Off",2,1);
				LCD_voidSendStringPos("3-Back",3,1);
			}
			room_state = KPD_u8GetPressKey();
			if(room_state == '3')
			{
				*flag=2;
			}
			SPI_u8Tranceive(room_state);
			break;
		case '3':
			if(*flag==3)
			{
				*flag=4;
				LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				LCD_voidSendStringPos("1-Turn On",1,1);
				LCD_voidSendStringPos("2-Turn Off",2,1);
				LCD_voidSendStringPos("3-Back",3,1);
			}
			room_state = KPD_u8GetPressKey();
			if(room_state == '3')
			{
				*flag=2;
			}
			SPI_u8Tranceive(room_state);
			break;
		case '4':
			if(*flag==3)
			{
				*flag=4;
				LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				LCD_voidSendStringPos("1-Turn On",1,1);
				LCD_voidSendStringPos("2-Turn Off",2,1);
				LCD_voidSendStringPos("3-Back",3,1);
			}
			room_state = KPD_u8GetPressKey();
			if(room_state == '3')
			{
			*flag=2;
			}
			SPI_u8Tranceive(room_state);
			break;
		case '5':
			*flag=1;
			*chose=KPD_CHECK_KEY;
			LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
			break;
			default :
			if(room != KPD_CHECK_KEY)
			{
				LCD_voidSendCommand(LCD_CLEAR_DISBLAY);
				LCD_voidSendStringPos("Invalid Chose ",1,1);
				_delay_ms(700);
			}
			break;
	}

}

