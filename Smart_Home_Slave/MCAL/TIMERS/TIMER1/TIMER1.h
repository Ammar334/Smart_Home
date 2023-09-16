/* 
 * File    : SERVO.c
 * Author  : Ammar.Yasser
 * SWC     : SERVO
 * Version : V1
 * Created on Monday : 28,8,2023 
 */
 
 
 #ifndef TIMER1_H
 #define TIMER1_H
 
 
 
 
#define TIMER1_MODE_1					0
#define TIMER1_MODE_2					1
#define TIMER1_MODE_3					2
#define TIMER1_MODE_4					3
#define TIMER1_MODE_5					4
#define TIMER1_MODE_6					5
#define TIMER1_MODE_7					6
#define TIMER1_MODE_8					7
#define TIMER1_MODE_9					8
#define TIMER1_MODE_10					9
#define TIMER1_MODE_11					10
#define TIMER1_MODE_12					11
#define TIMER1_MODE_13					12
#define TIMER1_MODE_14					13
#define TIMER1_MODE_15					14
#define TIMER1_MODE_16					15
		
#define	TIMER1_PRELOAD_VALUE			0

#define TIMER1_MODE						TIMER1_MODE_15

#define PRECASCALER_CLEAR_MASK			0b11111000

#define TIMER1_STOP						0
#define TIMER1_NOSCALER					1
#define TIMER1_8SCALER					2
#define TIMER1_64SCALER					3
#define TIMER1_256SCALER				4
#define TIMER1_1024SCALER				5
#define EXTERNAL_FALING					6
#define EXTERNAL_RISING					7

#define PRECASCALER_MODE				TIMER1_8SCALER
 
#define TIMER1_CLEAR_MASK_OC1A			0b00111111

#define TIMER1_OC1A_DISCONCTED			0x00
#define TIMER1_OC1A_TOGGLE 				0b01000000
#define TIMER1_OC1A_NON_INVERTING 		0b10000000
#define TIMER1_OC1A_INVERTING 			0b11000000

#define TIMER1_OC1A_ACTION				TIMER1_OC1A_NON_INVERTING

#define TIMER1_CLEAR_MASK_OC1B			0b11001111

#define TIMER1_OC1B_DISCONCTED			0x00
#define TIMER1_OC1B_TOGGLE 				0b00010000
#define TIMER1_OC1B_NON_INVERTING 		0b00100000
#define TIMER1_OC1B_INVERTING 			0b00110000

#define TIMER1_OC1B_ACTION				TIMER1_OC1B_NON_INVERTING

#define     ICU_FALLING_EDGE                            0
#define     ICU_RISING_EDGE                             1

 
 
void TIMER1_Init(void);
void TIMER1_voidSetOcr1A(u16 Copy_u8Value);
void TIMER1_voidSetOcr1B(u16 Copy_u8Value);
void Timer1_voidSetICR1Value(u16 Copy_u16Value);
void TIMER1_voidEnableOVInterrubt(void);
void TIMER1_voidDisableOVInterrubt(void);
void TIMER1_voidEnableCOMPAInterrubt(void);
void TIMER1_voidDisableCOMPAInterrubt(void);
void TIMER1_voidEnableCOMPBInterrubt(void);
void TIMER1_voidDisableCOMPBInterrubt(void);
void TIMER1_voidSetPreloadValue(u16 Copy_u16Value);
u16  TIMER1_u16ReadValue(void);
u16  TIMER1_u16ReadICR1Value(void);
void Timer1_voidTriggeredge(u8 Copy_u8Edge);
void Timer1_voidICUInterruptEnable(void);
void Timer1_voidICUInterruptDisable(void);


void TIMER1_SetCallBackOV   (void (*Copy_PFvoidName)(void));
void TIMER1_SetCallBackCOMPA(void (*Copy_PFvoidName)(void));
void TIMER1_SetCallBackCOMPB(void (*Copy_PFvoidName)(void));
void Timer1_voidICUSetCallBack(void (*Copy_pfNotification)(void));
 
 #endif
