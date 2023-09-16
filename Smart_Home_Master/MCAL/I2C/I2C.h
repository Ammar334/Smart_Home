/* 
 * File    : I2C.c
 * Author  : Ammar.Yasser
 * SWC     : I2C
 * Version : V1
 * Created on saterday: 2,9,2023 
 */

 #ifndef I2C_H
 #define I2C_H
 
 
 
 
 #define TWD0 		0
 
 
 
 
void I2C_voidMasterInit(void);
void I2C_voidSlaveInit(u8 Copy_u8SlaveAddress);

void I2C_voidStartCondition(void);
void I2C_voidStopCondition(void);

void I2C_voidMasterSendAddressWrite(u8 Copy_u8SlaveAddress);
void I2C_voidMasterSendAddressRead(u8 Copy_u8SlaveAddress);

void I2C_voidMasterSendData(u8 Copy_u8Data);
u8 I2C_u8MasterReadData(void);

u8 I2C_u8SlaveReadData(void);

 #endif