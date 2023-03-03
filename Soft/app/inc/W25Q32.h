#ifndef __W25Q32_H__
#define __W25Q32_H__
#include "spi.h"
#include "dma.h"
/*命令*/
#define W25_WRITE_ENABLE 					0x06			//写使能
#define W25_WRITE_DISABLE 				0x04			//写禁止
#define W25_READ_STATUS_REG 			0x05    	//读状态寄存器
#define W25_WRITE_STATUS_REG 			0x01    	//写状态寄存器
#define W25_READ_DATA 						0x03      //读数据
#define W25_FAST_READ_DATA 				0x0B			//快速读数据
#define W25_FAST_READ_DUAL				0x3B			//快速异步读数据
#define W25_PAGE_PROGRAM					0x02			//页编辑
#define W25_BLOCK_ERASE						0xD8			//块擦除
#define W25_SECTOR_ERASE					0x20			//扇区擦除
#define W25_CHIP_ERASE						0xC7			//片擦除
#define W25_POWER_DOWN						0xB9			//关机
#define W25_RELEASE_POWER_DOWN		0xAB			//释放关机

#define W25_CS_SET()		HAL_GPIO_WritePin(GPIOB, W25Q32_CS_Pin, GPIO_PIN_SET)
#define W25_CS_CLR()		HAL_GPIO_WritePin(GPIOB, W25Q32_CS_Pin, GPIO_PIN_RESET)

void Flash_Erase(uint32_t address);
void Flash_Write_Data(uint8_t *Data, uint8_t len, uint32_t address);
void Flash_Read_Data(uint8_t *Data, uint16_t len, uint32_t address);
void Flash_while_Write(uint8_t *Data, uint16_t len, uint32_t address, uint32_t lastlen);
#endif
