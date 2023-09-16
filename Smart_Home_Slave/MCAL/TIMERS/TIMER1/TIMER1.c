/* 
 * File    : SERVO.c
 * Author  : Ammar.Yasser
 * SWC     : SERVO
 * Version : V1
 * Created on Monday : 28,8,2023 
 */
 
#include <avr/io.h>
#include "../../../LIB/Bit_math.h"
#include "../../../LIB/data_types.h"
#include "../../../MCAL/DIO/DIO.h"
#include "TIMER1.h"
#include <avr/interrupt.h>

 
void (*TIMER1_PFvoidInt[4])(void) = {NULL};

 void TIMER1_Init(void)
 {
	 #if  TIMER1_MODE == TIMER1_MODE_1
		/*Select mode */
		CLEAR_BIT(TCCR1B,WGM13);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1A,WGM10);
	 
	 #elif TIMER1_MODE == TIMER1_MODE_2
		/*Select mode*/
		CLEAR_BIT(TCCR1B,WGM13);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1A,WGM10);


	 #elif  TIMER1_MODE == TIMER1_MODE_3
		/*Select mode*/
		CLEAR_BIT(TCCR1B,WGM13);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1A,WGM10);
	
	 #elif TIMER1_MODE == TIMER1_MODE_4
		/*Select mode */
		CLEAR_BIT(TCCR1B,WGM13);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1A,WGM10);

	 #elif  TIMER1_MODE == TIMER1_MODE_5
		/*Select mode */
		CLEAR_BIT(TCCR1B,WGM13);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1A,WGM10);

	 #elif TIMER1_MODE == TIMER1_MODE_6
		/*Select mode */
		CLEAR_BIT(TCCR1B,WGM13);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1A,WGM10);

	 #elif  TIMER1_MODE == TIMER1_MODE_7
		/*Select mode */
		CLEAR_BIT(TCCR1B,WGM13);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1A,WGM10);

	 #elif TIMER1_MODE == TIMER1_MODE_8
		/*Select mode */
		CLEAR_BIT(TCCR1B,WGM13);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1A,WGM10);

	 #elif  TIMER1_MODE == TIMER1_MODE_9
		/*Select mode */
		SET_BIT(TCCR1B,WGM13);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1A,WGM10); 

	 #elif TIMER1_MODE == TIMER1_MODE_10
		/*Select mode */
		SET_BIT(TCCR1B,WGM13);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1A,WGM10);

	 #elif  TIMER1_MODE == TIMER1_MODE_11
		/*Select mode */
		SET_BIT(TCCR1B,WGM13);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1A,WGM10);

	 #elif TIMER1_MODE == TIMER1_MODE_12
		/*Select mode */
		SET_BIT(TCCR1B,WGM13);
		CLEAR_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1A,WGM10);

	 #elif TIMER1_MODE == TIMER1_MODE_13
		/*Select mode */
		SET_BIT(TCCR1B,WGM13);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1A,WGM10);

	 
	 #elif  TIMER1_MODE == TIMER1_MODE_14
		/*Select mode */
		SET_BIT(TCCR1B,WGM13);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1A,WGM10);

	 #elif  TIMER1_MODE == TIMER1_MODE_15
		/*Select mode */
		SET_BIT(TCCR1B,WGM13);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1A,WGM11);
		CLEAR_BIT(TCCR1A,WGM10);

	 #elif TIMER1_MODE == TIMER1_MODE_16
		/*Select mode */
		SET_BIT(TCCR1B,WGM13);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1A,WGM10);
	 
	 #endif
	 
	TCCR1B &= PRECASCALER_CLEAR_MASK;
	TCCR1B |= PRECASCALER_MODE;
	
	TCCR1A &= TIMER1_CLEAR_MASK_OC1A;
	TCCR1A |= TIMER1_OC1A_ACTION;
	
	TCCR1A &= TIMER1_CLEAR_MASK_OC1B;
	TCCR1A |= TIMER1_OC1B_ACTION;
	 
 }
 
void TIMER1_voidSetOcr1A(u16 Copy_u8Value)
{
	OCR1A = Copy_u8Value;
}

void TIMER1_voidSetOcr1B(u16 Copy_u8Value)
{
	OCR1B = Copy_u8Value;
}

void Timer1_voidSetICR1Value(u16 Copy_u8Value)
{
	ICR1 = Copy_u8Value;
}
 
void TIMER1_voidEnableOVInterrubt(void)
{
	SET_BIT(TIMSK,TOIE1);

}

void TIMER1_voidDisableOVInterrubt(void)
{
	CLEAR_BIT(TIMSK,TOIE1);
}
void TIMER1_voidEnableCOMPAInterrubt(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void TIMER1_voidDisableCOMPAInterrubt(void)
{
	CLEAR_BIT(TIMSK,OCIE1A);
}
void TIMER1_voidEnableCOMPBInterrubt(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void TIMER1_voidDisableCOMPBInterrubt(void)
{
	CLEAR_BIT(TIMSK,OCIE1B);
}
void TIMER1_voidSetPreloadValue(u16 Copy_u16Value)
{
	TCNT1 = Copy_u16Value;
}
u16  TIMER1_u16ReadValue(void)
{
	return TCNT1;
}

u16  Timer1_u16ReadICR1Value(void)
{
    return ICR1;
}

void Timer1_voidTriggeredge(u8 Copy_u8Edge)
{
	switch(Copy_u8Edge)
	{
		case ICU_FALLING_EDGE:
			CLEAR_BIT(TCCR1B, ICES1);
		
		break;
		case ICU_RISING_EDGE:
			SET_BIT(TCCR1B, ICES1);
		break;
		
		default :
		break;
		
	}
}
void Timer1_voidICUInterruptEnable(void)
{
	SET_BIT(TIMSK, TICIE1);
}
	

void Timer1_voidICUInterruptDisable(void)
{
	CLEAR_BIT(TIMSK, TICIE1);
}


void TIMER1_SetCallBackOV   (void (*Copy_PFvoidName)(void))
{
	TIMER1_PFvoidInt[0] = Copy_PFvoidName;
}
void TIMER1_SetCallBackCOMPA(void (*Copy_PFvoidName)(void))
{
	TIMER1_PFvoidInt[1] = Copy_PFvoidName;
}
void TIMER1_SetCallBackCOMPB(void (*Copy_PFvoidName)(void))
{
	TIMER1_PFvoidInt[2] = Copy_PFvoidName;
}
void Timer1_voidICUSetCallBack(void (*Copy_pfNotification)(void))
{
	TIMER1_PFvoidInt[3] = Copy_pfNotification;
}

 
 ISR(TIMER1_OVF_vect)
 {
	 if(TIMER1_PFvoidInt[0] != NULL)
	 {
		 TIMER1_PFvoidInt[0]();
	 }
	 
 }
 
 ISR(TIMER1_COMPA_vect)
 {
	 if(TIMER1_PFvoidInt[1] != NULL)
	 {
		 TIMER1_PFvoidInt[1]();
	 }
 }
 
 ISR(TIMER1_COMPB_vect)
 {
	 if(TIMER1_PFvoidInt[2] != NULL)
	 {
		 TIMER1_PFvoidInt[2]();
	 }
 }
 
 ISR(TIMER1_CAPT_vect)
 {
	 if(TIMER1_PFvoidInt[3] != NULL)
	 {
		 TIMER1_PFvoidInt[3]();
	 }
 }
 
 
 
 
 
 
 
 
 
 
