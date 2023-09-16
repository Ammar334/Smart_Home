/* 
 * File    : ADC.h
 * Author  : Ammar.Yasser
 * SWC     : ADC
 * Version : V1
 * Created on Thrasday : 24,8,2023 
 */
 
 
 
 #ifndef ADC_H
 #define ADC_H
 
/*********Macro Declaration***********/

#define ADC_PORT		DIO_PORTA
#define ADC_REG			(*(volatile u16*)0x24)
#define CLEAR_MASK		0b11100000
 
#define ADC_CHANNEL0	0
#define ADC_CHANNEL1	1
#define ADC_CHANNEL2	2
#define ADC_CHANNEL3	3
#define ADC_CHANNEL4	4
#define ADC_CHANNEL5	5
#define ADC_CHANNEL6	6
#define ADC_CHANNEL7	7

/*********Function Declaration***********/
void ADC_voidInit(void);
u16  ADC_u16GetDigitalValue(u8 Copy_u8ChannelNum);
 #endif
