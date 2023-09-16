/* 
 * File    : SPI.c
 * Author  : Ammar.Yasser
 * SWC     : SPI
 * Version : V1
 * Created on Thrasday: 31,8,2023 
 */

#include <avr/io.h>
#include "../../LIB/Bit_math.h"
#include "../../LIB/data_types.h"
#include "SPI.h"
#include "../../MCAL/DIO/DIO.h"

 void SPI_voidInit(void)
 {
	 #if SPI_MODE == SPI_MASTER_MODE
	 
	 SET_BIT(SPCR,MSTR);
	 DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN5,DIO_OUTPUT);
	 DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN7,DIO_OUTPUT);
	 DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN4,DIO_OUTPUT);
	 DIO_voidSetPinvalue(DIO_PORTB,DIO_PIN4,DIO_LOW);
	 
	 #elif SPI_MODE == SPI_SLAVE_MODE
	 
	 DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN6,DIO_OUTPUT);
	 CLEAR_BIT(SPCR,MSTR);
	 #endif
	 //data order
	 SET_BIT(SPCR,DORD);
	 //clk polarty
	 CLEAR_BIT(SPCR,CPOL);
	 //clk phase
	 SET_BIT(SPCR,CPHA);
	 //set prescaler 
	 SET_BIT(SPCR,SPR0);
	 SET_BIT(SPCR,SPR1);
	 CLEAR_BIT(SPSR,SPI2X);
	 //spi enable
	 SET_BIT(SPCR,SPE);
 }
 u8 SPI_u8Tranceive(u8 Copy_u8Data)
 {
	 SPDR = Copy_u8Data;
	 
	 while(READ_BIT(SPSR,SPIF)==0);
	 
	 return SPDR;
	 
 }
