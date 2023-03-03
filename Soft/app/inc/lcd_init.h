#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "spi.h"
#include "tim.h"

#define USE_HORIZONTAL 0  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����
#define MAX_ARRAY 11520   //������ɫ�洢buff��С
#define COUT 10						//����Ļ�ֳɼ�����
#define LVGL_COUT 24			//��Ļ��ȵ�10/1



//-----------------LCD�˿ڶ���---------------- 

/* LCDƬѡ */
#define LCD_CS_Clr()	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_CS_Set()	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
/* LCD������������*/
#define LCD_DC_Clr()	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_RESET)
#define LCD_DC_Set()	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_SET)
/* LCD����Դ*/
#define LCD_BLK_Clr()  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 100);
#define LCD_BLK_Set()  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
/**/
#define LCD_RES_Clr()  HAL_GPIO_WritePin(LCD_RESTER_GPIO_Port, LCD_RESTER_Pin, GPIO_PIN_RESET)
#define LCD_RES_Set()  HAL_GPIO_WritePin(LCD_RESTER_GPIO_Port, LCD_RESTER_Pin, GPIO_PIN_SET)

void LCD_GPIO_Int(void);
void LCD_WR_DATA8(uint8_t dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t dat);//д��һ��ָ��
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��


#endif




