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
#define PE_Sensor_2_Pin GPIO_PIN_13
#define PE_Sensor_2_GPIO_Port GPIOC
#define PE_Sensor_2_EXTI_IRQn EXTI15_10_IRQn
#define SPARE_Pin GPIO_PIN_15
#define SPARE_GPIO_Port GPIOC
#define SPARE_EXTI_IRQn EXTI15_10_IRQn
#define PE_Sensor_1_Pin GPIO_PIN_0
#define PE_Sensor_1_GPIO_Port GPIOC
#define PE_Sensor_1_EXTI_IRQn EXTI0_IRQn
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
#define PE_Sensor_3_Pin GPIO_PIN_4
#define PE_Sensor_3_GPIO_Port GPIOA
#define PE_Sensor_3_EXTI_IRQn EXTI4_IRQn
#define ROPE_Pin GPIO_PIN_6
#define ROPE_GPIO_Port GPIOA
#define ROPEA7_Pin GPIO_PIN_7
#define ROPEA7_GPIO_Port GPIOA
#define A_RX_Pin GPIO_PIN_5
#define A_RX_GPIO_Port GPIOC
#define Line_Sensor_L_Pin GPIO_PIN_0
#define Line_Sensor_L_GPIO_Port GPIOB
#define Line_Sensor_R_Pin GPIO_PIN_1
#define Line_Sensor_R_GPIO_Port GPIOB
#define A_TX_Pin GPIO_PIN_10
#define A_TX_GPIO_Port GPIOB
#define Photo_Interrupt_Pin GPIO_PIN_12
#define Photo_Interrupt_GPIO_Port GPIOB
#define Photo_Interrupt_EXTI_IRQn EXTI15_10_IRQn
#define Self_Pos_PE_1_Pin GPIO_PIN_14
#define Self_Pos_PE_1_GPIO_Port GPIOB
#define Self_Pos_PE_1_EXTI_IRQn EXTI15_10_IRQn
#define LED_Pin GPIO_PIN_15
#define LED_GPIO_Port GPIOB
#define MOTOR_TX_Pin GPIO_PIN_6
#define MOTOR_TX_GPIO_Port GPIOC
#define MOTOR_RX_Pin GPIO_PIN_7
#define MOTOR_RX_GPIO_Port GPIOC
#define LIMIT_L_V4_Pin GPIO_PIN_8
#define LIMIT_L_V4_GPIO_Port GPIOC
#define Self_Pos_Gyro_SDA_Pin GPIO_PIN_9
#define Self_Pos_Gyro_SDA_GPIO_Port GPIOC
#define Self_Pos_Gyro_SCL_Pin GPIO_PIN_8
#define Self_Pos_Gyro_SCL_GPIO_Port GPIOA
#define PC_TX_Pin GPIO_PIN_9
#define PC_TX_GPIO_Port GPIOA
#define PC_RX_Pin GPIO_PIN_10
#define PC_RX_GPIO_Port GPIOA
#define Self_Pos_PE_2_Pin GPIO_PIN_11
#define Self_Pos_PE_2_GPIO_Port GPIOA
#define Self_Pos_PE_2_EXTI_IRQn EXTI15_10_IRQn
#define Under_SW_V3_4_Pin GPIO_PIN_12
#define Under_SW_V3_4_GPIO_Port GPIOA
#define Y_OD_Pin GPIO_PIN_15
#define Y_OD_GPIO_Port GPIOA
#define B_TX_Pin GPIO_PIN_10
#define B_TX_GPIO_Port GPIOC
#define B_RX_Pin GPIO_PIN_11
#define B_RX_GPIO_Port GPIOC
#define LED_TX_Pin GPIO_PIN_12
#define LED_TX_GPIO_Port GPIOC
#define LED_RX_Pin GPIO_PIN_2
#define LED_RX_GPIO_Port GPIOD
#define Y_ODB3_Pin GPIO_PIN_3
#define Y_ODB3_GPIO_Port GPIOB
#define LIMIT_F_V2_Pin GPIO_PIN_5
#define LIMIT_F_V2_GPIO_Port GPIOB
#define Robot_Gyro_SCL_Pin GPIO_PIN_8
#define Robot_Gyro_SCL_GPIO_Port GPIOB
#define Robot_Gyro_SDA_Pin GPIO_PIN_9
#define Robot_Gyro_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
