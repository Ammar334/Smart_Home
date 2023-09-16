
/* 
 * File    : KEYPAD.c
 * Author  : Ammar.Yasser
 * SWC     : KPD
 * Version : V1
 * Created on Monday : 21,8,2023 
 */

#ifndef KEYPAD_H
#define KEYPAD_H


/*********Macro Declaration***********/

#define KPD_PORT				DIO_PORTA

#define OUTPUTROW_INPUTCOL		0x0F
#define INPUTROW_OUTPUTCOL		0xF0
#define KPD_CONTROL				OUTPUTROW_INPUTCOL

#define ROWS				4
#define COULMNS				3

#define KPD_R1_PIN			DIO_PIN0
#define KPD_R2_PIN			DIO_PIN1
#define KPD_R3_PIN			DIO_PIN2
#define KPD_R4_PIN			DIO_PIN3

#define KPD_C1_PIN			DIO_PIN4
#define KPD_C2_PIN			DIO_PIN5
#define KPD_C3_PIN			DIO_PIN6
#define KPD_C4_PIN			DIO_PIN7

#define KPD_CHECK_KEY		0xFF

/*********Function Declaration***********/
void KPD_voidInit(void);
u8 KPD_u8GetPressKey(void);




#endif
