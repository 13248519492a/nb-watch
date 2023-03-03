#include "lcd.h"
volatile uint8_t Data[MAX_ARRAY];
/******************************************************************************
      ����˵������ָ�����������ɫ
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
								color       Ҫ������ɫ
      ����ֵ��  ��
******************************************************************************/
void Fill_color(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{
	uint32_t num = (xend - xsta) * (yend - ysta) * 2;
	LCD_Address_Set(xsta, ysta, xend, yend);//������ʾ��Χ
	if(num > MAX_ARRAY)
	{
		num /= COUT;
		for(uint8_t j = 0; j < COUT; j++)
		{
			for(uint16_t i = 0; i < num; i++)
			{
				Data[i] = color >> 8;
				i++;
				Data[i] = color;
			}
			LCD_CS_Clr();
			HAL_SPI_Transmit(&hspi1, (uint8_t *)Data, num, 1000);
			LCD_CS_Set();
		}
	}
	else
	{
		for(uint16_t i = 0; i < num; i++)
		{
			Data[i] = color >> 8;
			i++;
			Data[i] = color;
		}
		LCD_CS_Clr();
		HAL_SPI_Transmit(&hspi1, (uint8_t *)Data, num, 1000);
		LCD_CS_Set();
	}
}


/******************************************************************************
      ����˵����lvgl��ʾ����
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
								color       Ҫ������ɫ
      ����ֵ��  ��
******************************************************************************/
void lv_Fill_color(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend, uint16_t *color)
{
	uint16_t num;
	uint16_t k = 0;
	num = (xend - xsta + 1) * (yend - ysta + 1) * 2;
	LCD_Address_Set(xsta, ysta, xend, yend);
	for(uint16_t i=0; i < num; i++)
	{
		Data[i] = (color[k] >> 8);
		i++;
		Data[i] = color[k];
		k++;
	}
	LCD_CS_Clr();
	HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)Data, num);
}


/******************************************************************************
      ����˵����lvgl��ʾͼƬ����
      ������ݣ�x,y   ��ʼ����
                length,width   ���ȿ��
								pic[]       ͼƬ����
      ����ֵ��  ��
******************************************************************************/
void lv_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width, uint8_t pic[])
{
	uint32_t num = (length - x) * (width - y) * 2;
	LCD_Address_Set(x,y, length-x-1 , width-y-1);
	for(uint32_t i = 0; i < num; i++)
	{
		Data[i] = pic[i];
	}
	LCD_CS_Clr();
	HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)Data, num);
}
	
