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
extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;


extern I2C_HandleTypeDef hi2c3;
extern I2C_HandleTypeDef hi2c1;
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
#define PE_Sensor_B_Pin GPIO_PIN_13
#define PE_Sensor_B_GPIO_Port GPIOC
#define PE_Sensor_B_EXTI_IRQn EXTI15_10_IRQn
#define SPARE_Pin GPIO_PIN_15
#define SPARE_GPIO_Port GPIOC
#define SPARE_EXTI_IRQn EXTI15_10_IRQn
#define PE_Sensor_T_Pin GPIO_PIN_0
#define PE_Sensor_T_GPIO_Port GPIOC
#define PE_Sensor_T_EXTI_IRQn EXTI0_IRQn
#define Under_SW_V1_2_Pin GPIO_PIN_1
#define Under_SW_V1_2_GPIO_Port GPIOC
#define LIMIT_F_V3_Pin GPIO_PIN_2
#define LIMIT_F_V3_GPIO_Port GPIOC
#define LIMIT_L_V3_Pin GPIO_PIN_3
#define LIMIT_L_V3_GPIO_Port GPIOC
#define X_OD_Pin GPIO_PIN_0
#define X_OD_GPIO_Port GPIOA
#define X_ODA1_Pin GPIO_PIN_1
#define X_ODA1_GPIO_Port GPIOA
#define PE_Sensor_F_Pin GPIO_PIN_4
#define PE_Sensor_F_GPIO_Port GPIOA
#define PE_Sensor_F_EXTI_IRQn EXTI4_IRQn
#define SOLENOID_RX_Pin GPIO_PIN_5
#define SOLENOID_RX_GPIO_Port GPIOC
#define SOLENOID_TX_Pin GPIO_PIN_10
#define SOLENOID_TX_GPIO_Port GPIOB
#define Under_SW_V2_3_Pin GPIO_PIN_14
#define Under_SW_V2_3_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_15
#define LED_GPIO_Port GPIOB
#define MOTOR_TX_Pin GPIO_PIN_6
#define MOTOR_TX_GPIO_Port GPIOC
#define MOTOR_RX_Pin GPIO_PIN_7
#define MOTOR_RX_GPIO_Port GPIOC
#define LIMIT_L_V4_Pin GPIO_PIN_8
#define LIMIT_L_V4_GPIO_Port GPIOC
#define ToF_L_SDA_Pin GPIO_PIN_9
#define ToF_L_SDA_GPIO_Port GPIOC
#define ToF_L_SCL_Pin GPIO_PIN_8
#define ToF_L_SCL_GPIO_Port GPIOA
#define PC_TX_Pin GPIO_PIN_9
#define PC_TX_GPIO_Port GPIOA
#define PC_RX_Pin GPIO_PIN_10
#define PC_RX_GPIO_Port GPIOA
#define Under_SW_V1_4_Pin GPIO_PIN_11
#define Under_SW_V1_4_GPIO_Port GPIOA
#define Under_SW_V3_4_Pin GPIO_PIN_12
#define Under_SW_V3_4_GPIO_Port GPIOA
#define Y_OD_Pin GPIO_PIN_15
#define Y_OD_GPIO_Port GPIOA
#define Controller_TX_Pin GPIO_PIN_10
#define Controller_TX_GPIO_Port GPIOC
#define Controller_RX_Pin GPIO_PIN_11
#define Controller_RX_GPIO_Port GPIOC
#define LED_TX_Pin GPIO_PIN_12
#define LED_TX_GPIO_Port GPIOC
#define LED_RX_Pin GPIO_PIN_2
#define LED_RX_GPIO_Port GPIOD
#define Y_ODB3_Pin GPIO_PIN_3
#define Y_ODB3_GPIO_Port GPIOB
#define LIMIT_F_V2_Pin GPIO_PIN_5
#define LIMIT_F_V2_GPIO_Port GPIOB
#define Gyro_ToF_F_SCL_Pin GPIO_PIN_8
#define Gyro_ToF_F_SCL_GPIO_Port GPIOB
#define Gyro_ToF_F_SDA_Pin GPIO_PIN_9
#define Gyro_ToF_F_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
