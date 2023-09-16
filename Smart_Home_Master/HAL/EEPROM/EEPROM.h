/* 
 * File    : EEPROM.h
 * Author  : Ammar.Yasser
 * SWC     : EEPROM
 * Version : V1
 * Created on saterday: 2,9,2023 
 */

 #ifndef EEPROM_H
 #define EEPROM_H
 
 #define A2_PIN		0
 
 
 void EEPROM_voidWriteData(u8 Copy_u8Data,u16 Copy_u16Address);
 u8 EEPROM_voidReadData(u16 Copy_u16Address);
 
 #endif
 