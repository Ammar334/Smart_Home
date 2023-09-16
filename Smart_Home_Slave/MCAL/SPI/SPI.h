/* 
 * File    : SPI.c
 * Author  : Ammar.Yasser
 * SWC     : SPI
 * Version : V1
 * Created on Thrasday: 31,8,2023 
 */
 #ifndef SPI_H
 #define SPI_H
 
 #define SPI_MODE				SPI_SLAVE_MODE
 
 #define SPI_MASTER_MODE		0
 #define SPI_SLAVE_MODE			1
 
 
 
 
 void SPI_voidInit(void);
 u8 SPI_u8Tranceive(u8 Copy_u8Data);
 
 
 
 
 
 #endif
 
