#include "W25Q32.h"


/******************************************************************************
      函数说明：确认W25Q32是否在忙
      入口数据：无
      返回值：  无
******************************************************************************/
void Flash_CheckStat(void)
{
	 uint8_t stat=1;
	 uint8_t cmd[] = {W25_READ_STATUS_REG};
	 while(stat&1<<0)
	 {
		 W25_CS_CLR();
		 HAL_SPI_Transmit(&hspi1, cmd, 1, 1000);
		 HAL_SPI_Receive(&hspi1, &stat, 1, 1000);
		 W25_CS_SET();
	 }
}


/******************************************************************************
      函数说明：W25Q32写使能
      入口数据：无
      返回值：  无
******************************************************************************/
void Flash_Write_Enable(void)
{
	uint8_t cmd[] = {W25_WRITE_ENABLE};
	W25_CS_CLR();
	HAL_SPI_Transmit(&hspi1, cmd, 1, 1000);
	W25_CS_SET();
}




/******************************************************************************
      函数说明：W25Q32片擦除
      入口数据：address 擦除开始地址
      返回值：  无
******************************************************************************/
void Flash_Erase_Page(uint32_t address)
{
	 uint8_t cmd[4];
	 cmd[0] = W25_PAGE_PROGRAM;
	 cmd[1] = (uint8_t)(address >> 16);
	 cmd[2] = (uint8_t)(address >> 8);
	 cmd[3] = (uint8_t)(address);
	 Flash_Write_Enable();
	 W25_CS_CLR();
	 HAL_SPI_Transmit(&hspi1, cmd, 4, 1000);
	 W25_CS_SET();
	 Flash_CheckStat();
}
/******************************************************************************
      函数说明：W25Q32块擦除
      入口数据：address 擦除开始地址
      返回值：  无
******************************************************************************/
void Flash_Erase_Block(uint32_t address)
{
	 uint8_t cmd[4];
	 cmd[0] = W25_BLOCK_ERASE;
	 cmd[1] = (uint8_t)(address >> 16);
	 cmd[2] = (uint8_t)(address >> 8);
	 cmd[3] = (uint8_t)(address);
	 Flash_Write_Enable();
	 W25_CS_CLR();
	 HAL_SPI_Transmit(&hspi1, cmd, 4, 1000);
	 W25_CS_SET();
	 Flash_CheckStat();
}


/******************************************************************************
      函数说明：W25Q32写数据函数
      入口数据：Data	写入的数据
			          len	数据的长度(最多写入255)
								address	写数据开始地址
      返回值：  无
******************************************************************************/
void Flash_Write_Data(uint8_t *Data, uint8_t len, uint32_t address)
{
	 uint8_t cmd[4];
	 cmd[0] = W25_PAGE_PROGRAM;
	 cmd[1] = (uint8_t)(address >> 16);
	 cmd[2] = (uint8_t)(address >> 8);
	 cmd[3] = (uint8_t)(address);
	 Flash_Write_Enable();
	 W25_CS_CLR();
	 HAL_SPI_Transmit(&hspi1, cmd, 4, 1000);
	 HAL_SPI_Transmit(&hspi1, Data, len, 1000);
	 W25_CS_SET();
	 Flash_CheckStat();
}


/******************************************************************************
      函数说明：W25Q32读数据函数
      入口数据：Data	读出的数据
			          len	需要读的长度(最多读65535)
								address	读数据开始地址
      返回值：  无
******************************************************************************/
void Flash_Read_Data(uint8_t *Data, uint16_t len, uint32_t address)
{
	 uint8_t cmd[4];
	 cmd[0] = W25_READ_DATA;
	 cmd[1] = (uint8_t)(address >> 16);
	 cmd[2] = (uint8_t)(address >> 8);
	 cmd[3] = (uint8_t)(address);
	 W25_CS_CLR();
	 HAL_SPI_Transmit(&hspi1, cmd, 4, 1000);
	 HAL_SPI_Receive(&hspi1, Data, len, 1000);
	 W25_CS_SET();
}



/******************************************************************************
      函数说明：W25Q32循环写数据函数
      入口数据：Data	写入的数据
			          len	循环写入次数(数据总长度 / 256)
								address	写数据开始地址
								lastlen	循环写入后最后一次的长度(数据总长度 - 256 * len)
      返回值：  无
******************************************************************************/
void Flash_while_Write(uint8_t *Data, uint16_t len, uint32_t address, uint32_t lastlen)
{
	 uint8_t i;
	 for(i = 0; i < len; i++)
	 {
		 Flash_Write_Data(Data + i * 256, 255, address + 256 * i);
	 }
	 Flash_Write_Data(Data + i * 256, lastlen, address + 256 * i);
}
