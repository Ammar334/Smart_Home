/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ACC
 */
#include <avr/io.h>
#include <stdio.h>
#include "MCAL/DIO/DIO.h"
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>
#include "MCAL/SPI/SPI.h"
#include "MCAL/TIMERS/TIMER1/TIMER1.h"

int main(void)
{
	u8 l_data = 0;
	u8 l_room=0;
	u8 mode =0;
	u16 l_Air_coundition = 9999;
	u8 l_air_mode =0;
	u8 l_heater_mode = 0 ;
	u16 l_heater = 9999;
	u8 true_value =0;
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN0,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN1,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN4,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);
	SPI_voidInit();
	TIMER1_Init();
	Timer1_voidSetICR1Value(19999);
	while(1)
	{
		mode = SPI_u8Tranceive(0xff);

		if(mode == '1')
		{
			l_air_mode = SPI_u8Tranceive(0xff);
			TIMER1_voidSetOcr1A(l_Air_coundition);
			TIMER1_voidSetOcr1B(0);
			switch(l_air_mode)
			{
				case '1':
					if(l_Air_coundition>2000)
					{
						l_Air_coundition -= 2000;//10% Duty --> 2000
					}
					else
					{
						l_Air_coundition = 0;
						//Duty 1%
					}
					break;
				case '2':
					if(l_Air_coundition < 17999)
					{
						l_Air_coundition +=2000;//10% Duty --> 2000
					}
					else
					{
						l_Air_coundition =19999;
						//Duty 100%
					}
					break;
				case '3':
					l_Air_coundition = 0;
					break;
			}

		}
		else if(mode == '2')
		{
			l_heater_mode = SPI_u8Tranceive(0xff);
			TIMER1_voidSetOcr1B(l_heater);
			TIMER1_voidSetOcr1A(0);
			switch(l_heater_mode)
			{
				case '1':
					if(l_heater<17999)
					{
						l_heater +=2000;//10% Duty --> 200
					}
					else
					{
						//Duty = 100%
						l_heater = 19999;
					}
					break;
				case '2':
					if(l_heater > 2000)
					{
						l_heater -=2000;//10% Duty --> 200
					}
					else
					{
						//Duty = 1%
						l_heater =0;
					}
					break;
				case '3':
						l_heater = 0;
						break;
			}

		}
		else if(mode == '3')
		{
			true_value = SPI_u8Tranceive(0xff);
			TIMER1_voidSetOcr1B(l_heater);
			TIMER1_voidSetOcr1A(l_Air_coundition);
			if(true_value <=5)
			{
				//Duty = 100%
				l_heater = 19999;
				l_Air_coundition = 0;
			}
			else if(true_value <10)
			{
				//Duty = 80%
				l_heater = 15999;
				l_Air_coundition = 0;
			}
			else if(true_value <=16)
			{
				//Duty = 60%
				l_heater = 11999;
				l_Air_coundition = 0;
			}
			else if(true_value <=20)
			{
				//Duty = 30%
				l_heater = 5999;
				l_Air_coundition = 0;
			}
			else if(true_value <=23)
			{
				//Duty = 0%
				l_heater = 0;
				l_Air_coundition = 0;
			}
			else if(((true_value >23)&&(true_value <30)))
			{
				//Duty = 20%
				l_Air_coundition = 3999;
				l_heater = 0;
			}
			else if ((true_value <35)&&(true_value >=30))
			{
				//Duty = 40%
				l_Air_coundition = 7999;
				l_heater = 0;
			}
			else if((true_value <40)&&(true_value >=35))
			{
				//Duty = 60%
				l_Air_coundition = 11999;
				l_heater = 0;
			}
			else if(true_value >=40)
			{
				//Duty = 100%
				l_Air_coundition = 19999;
				l_heater = 0;
			}
		}
		else if(mode == '4')
		{
			l_room = SPI_u8Tranceive(0xFF);
			switch(l_room)
			{
				case '1':
					l_data = SPI_u8Tranceive(0xFF);
					switch(l_data)
					{
						case '1':
							DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN0,DIO_HIGH);
							break;
						case '2':
							DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN0,DIO_LOW);
							break;
					}
					break;
				case '2':
					l_data = SPI_u8Tranceive(0xFF);
					switch(l_data)
					{
						case '1':
							DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN1,DIO_HIGH);
							break;
						case '2':
							DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN1,DIO_LOW);
							break;
					}
					break;
				case '3':
					l_data = SPI_u8Tranceive(0xFF);
					switch(l_data)
					{
						case '1':
							DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
							break;
						case '2':
							DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN2,DIO_LOW);
							break;
					}
					break;
				case '4':
					l_data = SPI_u8Tranceive(0xFF);
					switch(l_data)
					{
						case '1':
							DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN3,DIO_HIGH);
							break;
						case '2':
							DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN3,DIO_LOW);
							break;
					}

					break;
			}

		}else if(mode == '5')
		{
			DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN3,DIO_LOW);
			DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN2,DIO_LOW);
			DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN1,DIO_LOW);
			DIO_voidSetPinvalue(DIO_PORTC,DIO_PIN0,DIO_LOW);
			TIMER1_voidSetOcr1A(0);
			TIMER1_voidSetOcr1B(0);

		}
	}

	return 0;
}






