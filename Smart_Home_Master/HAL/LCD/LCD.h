
/* 
 * File    : LCD.c
 * Author  : Ammar.Yasser
 * SWC     : DIO
 * Version : V1
 * Created on Sunday : 20,8,2023 
 */

#ifndef LCD_H
#define LCD_H

#include "../../LIB/data_types.h"

/*********Macro Declaration***********/

#define  LCD_DATA_PORT			DIO_PORTD

#define  LCD_CONTROL_PORT		DIO_PORTB

#define  LCD_RS_PIN				DIO_PIN1
#define  LCD_RW_PIN				DIO_PIN2
#define  LCD_EN_PIN				DIO_PIN3

#define  LCD_8BIT_FUNC_SET		0b00111000

#define  LCD_DISBLAY_ON_OFF		0b00001100

#define  LCD_CLEAR_DISBLAY		0b00000001

#define  LCD_ENTERY_MODE		0b00000110

#define LCD_CGRAM_START         0b01000000

#define DDRAM_START         	0x80

#define ROW1				 	1
#define ROW2				 	2
#define ROW3				 	3
#define ROW4				 	4

#define  LCD_RETURN_HOME		0b00000010
#define  LCD_4BIT_FUNC_SET		0b00101000

/*********Fuction Declaration***********/
void LCD_8BitvoidInit(void);
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidSendData(u8 Copy_u8Data);
void LCD_voidSendString(u8 *Copy_PAString);
void LCD_voidDrawCustomeCharPos(u8 *Copy_u8PAChar,u8 Copy_u8CharAddress,u8 Copy_u8Row,u8 Copy_u8Coulmn);
void LCD_voidSendDataPos(u8 Copy_u8Dat,u8 Copy_u8Row,u8 Copy_u8Coulmn);
void LCD_voidSendStringPos(u8 *Copy_PAString,u8 Copy_u8Row,u8 Copy_u8Coulmn);
void LCD_voidSendNumberPos(u32 Copy_u32number,u8 Copy_u8Row,u8 Copy_u8Coulmn);


void LCD_4BitvoidInit(void);
void LCD_4Bit_voidSendData(u8 Copy_u8Data);
void LCD_4Bit_voidSendCommand(u8 Copy_u8Command);
void LCD_4Bit_voidSendStringPos(u8 *Copy_PAString,u8 Copy_u8Row,u8 Copy_u8Coulmn);
void LCD_4Bit_voidSendString(u8 *Copy_PAString);
void LCD_4Bit_voidSendDataPos(u8 Copy_u8Data,u8 Copy_u8Row,u8 Copy_u8Coulmn);
void LCD_4Bit_voidDrawCustomeCharPos(u8 *Copy_u8PAChar,u8 Copy_u8CharAddress,u8 Copy_u8Row,u8 Copy_u8Coulmn);
void LCD_4Bit_voidSendNumberPos(u32 Copy_u32number,u8 Copy_u8Row,u8 Copy_u8Coulmn);


#endif
