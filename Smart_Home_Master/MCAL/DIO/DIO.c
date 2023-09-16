
/* 
 * File    : DIO.c
 * Author  : Ammar.Yasser
 * SWC     : DIO
 * Version : V1
 * Created on Tues Day : 17,8,2023 
 */

#include <avr/io.h>
#include "../../LIB/Bit_math.h"
#include "../../LIB/data_types.h"
#include "../../MCAL/DIO/DIO.h"

 void DIO_voidSetPinDirection(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Direction)
 {
		 
	 if(Copy_u8Direction == DIO_OUTPUT)
	 {
		switch(Copy_u8Port)
		{
			 case DIO_PORTA:
				SET_BIT(DDRA,Copy_u8Pin);
			 break;
			 case DIO_PORTB:
				SET_BIT(DDRB,Copy_u8Pin);
			 break;
			 case DIO_PORTC:
				SET_BIT(DDRC,Copy_u8Pin);
			 break;
			 case DIO_PORTD:				
				SET_BIT(DDRD,Copy_u8Pin);
			 break;
				default: ;
	 
			 }
	}
	else if(Copy_u8Direction == DIO_INPUT)
	{
		switch(Copy_u8Port)
		{
			case DIO_PORTA:
				CLEAR_BIT(DDRA,Copy_u8Pin);
			break;
			case DIO_PORTB:
				CLEAR_BIT(DDRB,Copy_u8Pin);
			break;
			case DIO_PORTC:
				CLEAR_BIT(DDRC,Copy_u8Pin);
			break;
			case DIO_PORTD:				
				CLEAR_BIT(DDRD,Copy_u8Pin);
			break;
			default: ;

				 
				 
		}
	}
	 
	 
 }
 
 
 void DIO_voidSetPinvalue (u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8value)
 {
	 if(Copy_u8value == DIO_HIGH)
	 {
		switch(Copy_u8Port)
		{
			 case DIO_PORTA:
				SET_BIT(PORTA,Copy_u8Pin);
			 break;
			 case DIO_PORTB:
				SET_BIT(PORTB,Copy_u8Pin);
			 break;
			 case DIO_PORTC:
				SET_BIT(PORTC,Copy_u8Pin);
			 break;
			 case DIO_PORTD:				
				SET_BIT(PORTD,Copy_u8Pin);
			 break;
				default: ;
	 
		}
	}
	else if(Copy_u8value == DIO_LOW)
	{
		switch(Copy_u8Port)
		{
			case DIO_PORTA:
				CLEAR_BIT(PORTA,Copy_u8Pin);
			break;
			case DIO_PORTB:
				CLEAR_BIT(PORTB,Copy_u8Pin);
			break;
			case DIO_PORTC:
				CLEAR_BIT(PORTC,Copy_u8Pin);
			break;
			case DIO_PORTD:				
				CLEAR_BIT(PORTD,Copy_u8Pin);
			break;
			default: ;

				 
				 
		}
	}
	 
 }
 u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin)
 {
	u8 l_value =0;
	switch(Copy_u8Port)
	{
		 case DIO_PORTA:
			 l_value = READ_BIT(PINA,Copy_u8Pin);
		 break;
		 case DIO_PORTB:
			 l_value = READ_BIT(PINB,Copy_u8Pin);
		 break;
		 case DIO_PORTC:
			 l_value = READ_BIT(PINC,Copy_u8Pin);
		 break;
		 case DIO_PORTD:				
			 l_value = READ_BIT(PIND,Copy_u8Pin);
		 break;
		 default: ;
	 
	}
	return l_value;
	
 }
 void DIO_voidTogglePinValue (u8 Copy_u8Port,u8 Copy_u8Pin)
 {
	switch(Copy_u8Port)
	{
		 case DIO_PORTA:
			TOGGLE_BIT(PORTA,Copy_u8Pin);
		 break;
		 case DIO_PORTB:
			TOGGLE_BIT(PORTB,Copy_u8Pin);
		 break;
		 case DIO_PORTC:
			TOGGLE_BIT(PORTC,Copy_u8Pin);
		 break;
		 case DIO_PORTD:				
			TOGGLE_BIT(PORTD,Copy_u8Pin);
		 break;
		 default: ;
	 
	}
 }

 void DIO_voidSetPortDirection(u8 Copy_u8Port,u8 Copy_u8Direction)
 {
	switch(Copy_u8Port)
	{
		 case DIO_PORTA:
			DDRA = Copy_u8Direction;
		 break;
		 case DIO_PORTB:
			DDRB = Copy_u8Direction;
		 break;
		 case DIO_PORTC:
			DDRC = Copy_u8Direction;
		 break;
		 case DIO_PORTD:				
			DDRD = Copy_u8Direction;
		 break;
		 default: ;
	 
	}
 }
 void DIO_voidSetPortvalue (u8 Copy_u8Port,u8 Copy_u8value)
 {
	switch(Copy_u8Port)
	{
		 case DIO_PORTA:
			PORTA = Copy_u8value;
		 break;
		 case DIO_PORTB:
			PORTB = Copy_u8value;
		 break;
		 case DIO_PORTC:
			PORTC = Copy_u8value;
		 break;
		 case DIO_PORTD:				
			PORTD = Copy_u8value;
		 break;
		 default: ;
	 
	}
 }
 u8   DIO_u8GetPortValue(u8 Copy_u8Port)
 {
	 u8 l_value = 0;
	switch(Copy_u8Port)
	{
		 case DIO_PORTA:
			 l_value = PINA;
		 break;
		 case DIO_PORTB:
			 l_value = PINB;
		 break;
		 case DIO_PORTC:
			 l_value = PINC;
		 break;
		 case DIO_PORTD:				
			 l_value = PIND;
		 break;
		 default: ;
	 
	}
	return l_value;
 }
