/* 
 * File    : I2C.c
 * Author  : Ammar.Yasser
 * SWC     : I2C
 * Version : V1
 * Created on saterday: 2,9,2023 
 */
#include <avr/io.h>
#include "../../LIB/Bit_math.h"
#include "../../LIB/data_types.h"
#include "I2C.h"
#include "../../MCAL/DIO/DIO.h"

void I2C_voidMasterInit(void)
{
	//TWSR = 00 Select Prescaler
	CLEAR_BIT(TWSR,TWPS0);
	CLEAR_BIT(TWSR,TWPS1);
	//TWBR = 12
	TWBR = 12;
	//Enable Ack
	SET_BIT(TWCR,TWEA);
	//Enable I2C
	SET_BIT(TWCR,TWEN);
	
}
void I2C_voidSlaveInit(u8 Copy_u8SlaveAddress)
{
	//Set Slave Address at TWAR
	TWAR = (Copy_u8SlaveAddress << 1);
	//Enable Ack
	SET_BIT(TWCR,TWEA);
	//Enable I2C
	SET_BIT(TWCR,TWEN);
}

void I2C_voidStartCondition(void)
{
	//enable start condition
	SET_BIT(TWCR,TWSTA);
	//clear flag
	SET_BIT(TWCR,TWINT);
	//Wait the start to end
	while((READ_BIT(TWCR,TWINT))==0);
	//Should check for Ack but simulation doesnt work with it
	//While((Twsr&0b11111000) != 0x08)  0x08 -->from data sheet
	
}
void I2C_voidStopCondition(void)
{
	//enable stop condition
	SET_BIT(TWCR,TWSTO);
	//clear flag
	SET_BIT(TWCR,TWINT);
	
	
}

void I2C_voidMasterSendAddressWrite(u8 Copy_u8SlaveAddress)
{
	//select address
	TWDR = Copy_u8SlaveAddress<<1;
	//select write operation
	CLEAR_BIT(TWDR,TWD0);
	//Disable start start condition
	CLEAR_BIT(TWCR,TWSTA);
	//Clear inturrebt falg
	SET_BIT(TWCR,TWINT);
	//Wait the start to end
	while((READ_BIT(TWCR,TWINT))==0);
	//Check ack
}
void I2C_voidMasterSendAddressRead(u8 Copy_u8SlaveAddress)
{
	//select address
	TWDR = Copy_u8SlaveAddress<<1;
	//select Read operation
	SET_BIT(TWDR,TWD0);
	//Disable start start condition
	CLEAR_BIT(TWCR,TWSTA);
	//Clear inturrebt falg
	SET_BIT(TWCR,TWINT);
	//Wait the start to end
	while((READ_BIT(TWCR,TWINT))==0);
	//Check ack
}

void I2C_voidMasterSendData(u8 Copy_u8Data)
{
	//write data in data reg
	TWDR = Copy_u8Data;
	//Clear inturrebt falg
	SET_BIT(TWCR,TWINT);
	//Wait the start to end
	while((READ_BIT(TWCR,TWINT))==0);
	//Check ack
}

u8 I2C_u8MasterReadData(void)
{
	//Clear inturrebt falg
	SET_BIT(TWCR,TWINT);
	//Wait the start to end
	while((READ_BIT(TWCR,TWINT))==0);
	//return data
	return TWDR;
}

u8 I2C_u8SlaveReadData(void)
{
	//wait to receive slave address
	while((TWSR&0xF8) != 0x60);
	//Clear inturrebt falg
	SET_BIT(TWCR,TWINT);
	//Wait to receive data
	while((TWSR&0xF8) != 0x80);
	//return data
	return TWDR;
}
