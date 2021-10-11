/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal_uart.h"
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
#define PE_Sensor_2_Pin GPIO_PIN_14
#define PE_Sensor_2_GPIO_Port GPIOC
#define PE_Sensor_2_EXTI_IRQn EXTI15_10_IRQn
#define PE_Sensor_1_Pin GPIO_PIN_0
#define PE_Sensor_1_GPIO_Port GPIOC
#define PE_Sensor_1_EXTI_IRQn EXTI0_IRQn
#define SIG_Pin GPIO_PIN_2
#define SIG_GPIO_Port GPIOC
#define PE_Sensor_3_Pin GPIO_PIN_4
#define PE_Sensor_3_GPIO_Port GPIOA
#define PE_Sensor_3_EXTI_IRQn EXTI4_IRQn
#define ROPE_Pin GPIO_PIN_6
#define ROPE_GPIO_Port GPIOA
#define ROPEA7_Pin GPIO_PIN_7
#define ROPEA7_GPIO_Port GPIOA
#define Photo_Interrupt_Pin GPIO_PIN_12
#define Photo_Interrupt_GPIO_Port GPIOB
#define PE_3_Pin GPIO_PIN_13
#define PE_3_GPIO_Port GPIOB
#define MOTOR_TX_Pin GPIO_PIN_6
#define MOTOR_TX_GPIO_Port GPIOC
#define MOTOR_RX_Pin GPIO_PIN_7
#define MOTOR_RX_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
