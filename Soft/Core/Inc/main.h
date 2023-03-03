/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "lcd_init.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lvgl_func.h"
#include "lv_port_indev_template.h"
#include "button.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_DOWN_Pin GPIO_PIN_13
#define BUTTON_DOWN_GPIO_Port GPIOC
#define BUTTON_DOWN_EXTI_IRQn EXTI15_10_IRQn
#define W25Q32_CS_Pin GPIO_PIN_12
#define W25Q32_CS_GPIO_Port GPIOB
#define BUTTON_UP_Pin GPIO_PIN_14
#define BUTTON_UP_GPIO_Port GPIOB
#define BUTTON_UP_EXTI_IRQn EXTI15_10_IRQn
#define BUTTON_PRESS_Pin GPIO_PIN_15
#define BUTTON_PRESS_GPIO_Port GPIOB
#define BUTTON_PRESS_EXTI_IRQn EXTI15_10_IRQn
#define LCD_NSS_Pin GPIO_PIN_8
#define LCD_NSS_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_15
#define LCD_CS_GPIO_Port GPIOA
#define LCD_Sck_Pin GPIO_PIN_3
#define LCD_Sck_GPIO_Port GPIOB
#define LCD_RECEIVE_Pin GPIO_PIN_4
#define LCD_RECEIVE_GPIO_Port GPIOB
#define LCD_SEND_Pin GPIO_PIN_5
#define LCD_SEND_GPIO_Port GPIOB
#define LCD_BLK_Pin GPIO_PIN_7
#define LCD_BLK_GPIO_Port GPIOB
#define LCD_RESTER_Pin GPIO_PIN_9
#define LCD_RESTER_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
