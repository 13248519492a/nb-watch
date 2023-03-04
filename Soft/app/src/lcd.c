#include "lcd.h"
#include "W25Q32.h"
volatile uint8_t Data[MAX_ARRAY];
volatile uint8_t Data_2[MAX_ARRAY];
/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/
void Fill_color(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{
	uint32_t num = (xend - xsta) * (yend - ysta) * 2;
	LCD_Address_Set(xsta, ysta, xend, yend);//设置显示范围
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
      函数说明：lvgl DMA显示函数
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/
void lv_Fill_color_DMA(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend, lv_color_t *color)
{
	uint16_t num;
	num = (xend - xsta + 1) * (yend - ysta + 1) * 2;
	LCD_Address_Set(xsta, ysta, xend, yend);
	for(uint16_t i=0; i < num; i++)
	{
		Data[i] = ((color->full) >> 8);
		i++;
		Data[i] = color->full;
		color++;
	}
	LCD_CS_Clr();
	HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)Data, num);
}



/******************************************************************************
      函数说明：lvgl DMA显示图片函数
      入口数据：x,y   起始坐标
                length,width   长度宽度
								pic[]       图片数组
      返回值：  无
******************************************************************************/
void lv_ShowPicture_DMA(uint16_t x,uint16_t y,uint16_t length,uint16_t width, uint8_t pic[])
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



void W25Q32_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width)
{
	uint8_t cmd[4];
	uint32_t address = 0x000000;
	cmd[0] = W25_READ_DATA;
	cmd[1] = (uint8_t)(address >> 16);
	cmd[2] = (uint8_t)(address >> 8);
	cmd[3] = (uint8_t)(address);
	LCD_CS_Clr();
	W25_CS_SET();
	LCD_Address_Set(0, 0, 240, 24);
	LCD_CS_Set();
	W25_CS_CLR();
	HAL_SPI_Transmit(&hspi1, cmd, 4, 1000);
	LCD_CS_Clr();
	HAL_SPI_Receive(&hspi1, (uint8_t *)Data, 11520, 1000);
	HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)Data, 11520);
	
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{

}

