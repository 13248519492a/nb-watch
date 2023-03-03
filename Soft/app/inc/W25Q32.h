#ifndef __W25Q32_H__
#define __W25Q32_H__
#include "spi.h"
#include "dma.h"
/*����*/
#define W25_WRITE_ENABLE 					0x06			//дʹ��
#define W25_WRITE_DISABLE 				0x04			//д��ֹ
#define W25_READ_STATUS_REG 			0x05    	//��״̬�Ĵ���
#define W25_WRITE_STATUS_REG 			0x01    	//д״̬�Ĵ���
#define W25_READ_DATA 						0x03      //������
#define W25_FAST_READ_DATA 				0x0B			//���ٶ�����
#define W25_FAST_READ_DUAL				0x3B			//�����첽������
#define W25_PAGE_PROGRAM					0x02			//ҳ�༭
#define W25_BLOCK_ERASE						0xD8			//�����
#define W25_SECTOR_ERASE					0x20			//��������
#define W25_CHIP_ERASE						0xC7			//Ƭ����
#define W25_POWER_DOWN						0xB9			//�ػ�
#define W25_RELEASE_POWER_DOWN		0xAB			//�ͷŹػ�

#define W25_CS_SET()		HAL_GPIO_WritePin(GPIOB, W25Q32_CS_Pin, GPIO_PIN_SET)
#define W25_CS_CLR()		HAL_GPIO_WritePin(GPIOB, W25Q32_CS_Pin, GPIO_PIN_RESET)

void Flash_Erase(uint32_t address);
void Flash_Write_Data(uint8_t *Data, uint8_t len, uint32_t address);
void Flash_Read_Data(uint8_t *Data, uint16_t len, uint32_t address);
void Flash_while_Write(uint8_t *Data, uint16_t len, uint32_t address, uint32_t lastlen);
#endif
