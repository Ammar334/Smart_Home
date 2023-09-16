/* 
 * File    : ADC.h
 * Author  : Ammar.Yasser
 * SWC     : ADC
 * Version : V1
 *Created on Thrasday : 24,8,2023 
 */
 
#include <avr/io.h>
#include "../../LIB/Bit_math.h"
#include "../../LIB/data_types.h"
#include "ADC.h"
#include <avr/interrupt.h>


void ADC_voidInit(void)
{
	/*Enable the adc */
	SET_BIT(ADCSRA,ADEN);
	/*Select v ref == Vcc*/
	SET_BIT(ADMUX,REFS0);
	CLEAR_BIT(ADMUX,REFS1);
	/*Select Right Adjst*/
	CLEAR_BIT(ADMUX,ADLAR);
	/*disable the auto triger*/
	CLEAR_BIT(ADCSRA,ADATE);
	/*Select Prescaler*/
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
	CLEAR_BIT(ADCSRA,ADPS0);
	
}

u16  ADC_u16GetDigitalValue(u8 Copy_u8ChannelNum)
{
	/*Clear first 5 bits*/
	ADMUX &= CLEAR_MASK;
	/*Select channel*/
	ADMUX |= Copy_u8ChannelNum;
	/*Start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait conversion to complete*/
	while((READ_BIT(ADCSRA,ADIF)) == 0);
	/*Clear the flag*/
	SET_BIT(ADCSRA,ADIF);
	/*Return the Digital value*/
	return ADC_REG;
	
}





