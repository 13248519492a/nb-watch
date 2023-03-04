#include "W25Q32.h"


/******************************************************************************
      ����˵����ȷ��W25Q32�Ƿ���æ
      ������ݣ���
      ����ֵ��  ��
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
      ����˵����W25Q32дʹ��
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void Flash_Write_Enable(void)
{
	uint8_t cmd[] = {W25_WRITE_ENABLE};
	W25_CS_CLR();
	HAL_SPI_Transmit(&hspi1, cmd, 1, 1000);
	W25_CS_SET();
}




/******************************************************************************
      ����˵����W25Q32Ƭ����
      ������ݣ�address ������ʼ��ַ
      ����ֵ��  ��
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
      ����˵����W25Q32�����
      ������ݣ�address ������ʼ��ַ
      ����ֵ��  ��
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
      ����˵����W25Q32д���ݺ���
      ������ݣ�Data	д�������
			          len	���ݵĳ���(���д��255)
								address	д���ݿ�ʼ��ַ
      ����ֵ��  ��
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
      ����˵����W25Q32�����ݺ���
      ������ݣ�Data	����������
			          len	��Ҫ���ĳ���(����65535)
								address	�����ݿ�ʼ��ַ
      ����ֵ��  ��
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
      ����˵����W25Q32ѭ��д���ݺ���
      ������ݣ�Data	д�������
			          len	ѭ��д�����(�����ܳ��� / 256)
								address	д���ݿ�ʼ��ַ
								lastlen	ѭ��д������һ�εĳ���(�����ܳ��� - 256 * len)
      ����ֵ��  ��
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
