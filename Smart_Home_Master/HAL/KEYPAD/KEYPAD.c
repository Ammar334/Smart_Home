
/* 
 * File    : KEYPAD.c
 * Author  : Ammar.Yasser
 * SWC     : KPD
 * Version : V1
 * Created on Monday : 21,8,2023 
 */
#include <avr/io.h>
#include <util/delay.h>
#include "../../LIB/Bit_math.h"
#include "../../LIB/data_types.h"
#include "../../MCAL/DIO/DIO.h"
#include "KEYPAD.h"

static u8 KPD_Au8Keys[ROWS][COULMNS] = { {'1','2','3'}
										,{'4','5','6'}
										,{'7','8','9'}
										,{'c','0','='}};

static u8 KPD_Au8RowPins[ROWS] = {KPD_R1_PIN,KPD_R2_PIN,KPD_R3_PIN,KPD_R4_PIN};
static u8 KPD_Au8COULMNSPins[COULMNS] = {KPD_C1_PIN,KPD_C2_PIN,KPD_C3_PIN};

void KPD_voidInit(void)
{
	DIO_voidSetPortDirection(KPD_PORT,KPD_CONTROL);
	DIO_voidSetPortvalue(KPD_PORT,0xFF);
}
	
	
u8 KPD_u8GetPressKey(void)
{
	u8 l_u8RowCounter =0;
	u8 l_u8CoulmnCounter =0;
	u8 l_u8PressedKey =0;
	u8 l_u8Flag=0;
	u8 l_u8ReturnedValue=KPD_CHECK_KEY;
	for(l_u8RowCounter=0;l_u8RowCounter<ROWS;l_u8RowCounter++)
	{
		DIO_voidSetPinvalue(KPD_PORT,KPD_Au8RowPins[l_u8RowCounter],DIO_LOW);
		for(l_u8CoulmnCounter=0;l_u8CoulmnCounter<COULMNS;l_u8CoulmnCounter++)
		{
			l_u8PressedKey = DIO_u8GetPinValue(KPD_PORT,KPD_Au8COULMNSPins[l_u8CoulmnCounter]);
			if(l_u8PressedKey == DIO_LOW)
			{
				_delay_ms(20);
				l_u8PressedKey = DIO_u8GetPinValue(KPD_PORT,KPD_Au8COULMNSPins[l_u8CoulmnCounter]);
				while(l_u8PressedKey == DIO_LOW )
				{
					l_u8PressedKey = DIO_u8GetPinValue(KPD_PORT,KPD_Au8COULMNSPins[l_u8CoulmnCounter]);
				}
				l_u8Flag = 1;
				break;
			}
		}
		DIO_voidSetPinvalue(KPD_PORT,KPD_Au8RowPins[l_u8RowCounter],DIO_HIGH);
		if(l_u8Flag==1)
		{
			l_u8ReturnedValue =  KPD_Au8Keys[l_u8RowCounter][l_u8CoulmnCounter];
			break;
		}
	}
	


	return l_u8ReturnedValue;

}
