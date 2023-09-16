/* 
 * File    : DIO.c
 * Author  : Ammar.Yasser
 * SWC     : DIO
 * Version : V1
 * Created on Tues Day : 17,8,2023 
 */
 #ifndef DIO_H
 #define DIO_H

#include "../../LIB/data_types.h"
  
/*********Macro Declaration***********/
#define  DIO_PIN0		0
#define  DIO_PIN1		1
#define  DIO_PIN2		2
#define  DIO_PIN3		3
#define  DIO_PIN4		4
#define  DIO_PIN5		5
#define  DIO_PIN6		6
#define  DIO_PIN7		7

#define  DIO_PORTA      0
#define  DIO_PORTB      1
#define  DIO_PORTC      2
#define  DIO_PORTD      3

#define  DIO_OUTPUT     1 
#define  DIO_INPUT      0 

#define  DIO_HIGH       1
#define  DIO_LOW		0

 
 void DIO_voidSetPinDirection(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Direction);
 void DIO_voidSetPinvalue (u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8value);
 u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin);
 void DIO_voidTogglePinValue (u8 Copy_u8Port,u8 Copy_u8Pin);

 void DIO_voidSetPortDirection(u8 Copy_u8Port,u8 Copy_u8Direction);
 void DIO_voidSetPortvalue (u8 Copy_u8Port,u8 Copy_u8value);
 u8   DIO_u8GetPortValue(u8 Copy_u8Port);

#endif
