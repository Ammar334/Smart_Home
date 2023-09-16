/* 
 * File    : EEPROM.c
 * Author  : Ammar.Yasser
 * SWC     : EEPROM
 * Version : V1
 * Created on saterday: 2,9,2023 
 */
#include <avr/io.h>
#include "../../LIB/Bit_math.h"
#include "../../LIB/data_types.h"
#include "EEPROM.h"
#include "../../MCAL/I2C/I2C.h"
#include <util/delay.h>

 void EEPROM_voidWriteData(u8 Copy_u8Data,u16 Copy_u16Address)
 {
	 I2C_voidStartCondition();
	 I2C_voidMasterSendAddressWrite((0x50)| (A2_PIN <<2) | (Copy_u16Address>>8));
	 I2C_voidMasterSendData(((u8)Copy_u16Address));
	 I2C_voidMasterSendData(Copy_u8Data);
	 I2C_voidStopCondition();
	 _delay_ms(10);
 }
 u8 EEPROM_voidReadData(u16 Copy_u16Address)
 {
	 u8 l_data =0;
	 I2C_voidStartCondition();

	 I2C_voidMasterSendAddressWrite((0x50) | (A2_PIN <<2) | (Copy_u16Address>>8));

	 I2C_voidMasterSendData(((u8)Copy_u16Address));

	 I2C_voidStartCondition();

	 I2C_voidMasterSendAddressRead((0x50) | (A2_PIN <<2) | (Copy_u16Address>>8));

	 l_data = I2C_u8MasterReadData();

	 I2C_voidStopCondition();
	 
	 return l_data;
 }
