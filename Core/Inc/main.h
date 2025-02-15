/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define Light_Sensor_Pin GPIO_PIN_0
#define Light_Sensor_GPIO_Port GPIOA
#define Temp_Sensor_Pin GPIO_PIN_1
#define Temp_Sensor_GPIO_Port GPIOA
#define Beeper_Pin GPIO_PIN_2
#define Beeper_GPIO_Port GPIOA
#define BTN1_Pin GPIO_PIN_5
#define BTN1_GPIO_Port GPIOA
#define BTN1_EXTI_IRQn EXTI9_5_IRQn
#define ENCODERA_Pin GPIO_PIN_6
#define ENCODERA_GPIO_Port GPIOA
#define ENCODERB_Pin GPIO_PIN_7
#define ENCODERB_GPIO_Port GPIOA
#define BTN2_Pin GPIO_PIN_0
#define BTN2_GPIO_Port GPIOB
#define BTN2_EXTI_IRQn EXTI0_IRQn
#define BTN3_Pin GPIO_PIN_1
#define BTN3_GPIO_Port GPIOB
#define BTN3_EXTI_IRQn EXTI1_IRQn
#define MPU6050_SCL_Pin GPIO_PIN_10
#define MPU6050_SCL_GPIO_Port GPIOB
#define MPU6050_SDA_Pin GPIO_PIN_11
#define MPU6050_SDA_GPIO_Port GPIOB
#define BTN4_Pin GPIO_PIN_12
#define BTN4_GPIO_Port GPIOB
#define BTN4_EXTI_IRQn EXTI15_10_IRQn
#define SERVO_Pin GPIO_PIN_8
#define SERVO_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_9
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_10
#define LED2_GPIO_Port GPIOA
#define LED3_Pin GPIO_PIN_11
#define LED3_GPIO_Port GPIOA
#define LED4_Pin GPIO_PIN_12
#define LED4_GPIO_Port GPIOA
#define OLED_SCL_Pin GPIO_PIN_6
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_7
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
