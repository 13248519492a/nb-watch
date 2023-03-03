#include "button.h"
Button_State button_state = Button_null;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == BUTTON_DOWN_Pin)
	{
		if(HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin) == 0)
			button_state = Button_right;
		else
			button_state = Button_null;
	}
	if(GPIO_Pin == BUTTON_UP_Pin)
	{
		if(HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin) == 0)
			button_state = Button_left;
		else
			button_state = Button_null;
	}
	if(GPIO_Pin == BUTTON_PRESS_Pin)
	{
		if(HAL_GPIO_ReadPin(BUTTON_PRESS_GPIO_Port, BUTTON_PRESS_Pin) == 0)
			button_state = Button_press;
		else
			button_state = Button_null;
	}
}

