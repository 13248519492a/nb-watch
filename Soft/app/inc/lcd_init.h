#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "spi.h"
#include "tim.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏
#define MAX_ARRAY 11520   //设置颜色存储buff大小
#define COUT 10						//把屏幕分成几部分
#define LVGL_COUT 24			//屏幕宽度的10/1



//-----------------LCD端口定义---------------- 

/* LCD片选 */
#define LCD_CS_Clr()	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_CS_Set()	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
/* LCD数据命令引脚*/
#define LCD_DC_Clr()	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_RESET)
#define LCD_DC_Set()	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_SET)
/* LCD背光源*/
#define LCD_BLK_Clr()  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 100);
#define LCD_BLK_Set()  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
/**/
#define LCD_RES_Clr()  HAL_GPIO_WritePin(LCD_RESTER_GPIO_Port, LCD_RESTER_Pin, GPIO_PIN_RESET)
#define LCD_RES_Set()  HAL_GPIO_WritePin(LCD_RESTER_GPIO_Port, LCD_RESTER_Pin, GPIO_PIN_SET)

void LCD_GPIO_Int(void);
void LCD_WR_DATA8(uint8_t dat);//写入一个字节
void LCD_WR_DATA(uint16_t dat);//写入两个字节
void LCD_WR_REG(uint8_t dat);//写入一个指令
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//设置坐标函数
void LCD_Init(void);//LCD初始化


#endif




