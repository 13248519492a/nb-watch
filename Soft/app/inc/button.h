#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "gpio.h"
typedef enum{
	Button_null = 0,
	Button_up = 1,
	Button_down = 2,
	Button_left = 3,
	Button_right = 4,
	Button_press = 5
}Button_State;
#endif

