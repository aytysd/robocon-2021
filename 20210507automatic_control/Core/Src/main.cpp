/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Function.hpp"
#include "PWM.hpp"
#include "stdio.h"
#include "Self_Pos.hpp"
#include "hGPIO.hpp"
#include "Init_Move.hpp"
#include "LED.hpp"
#include "Error_Handling.hpp"
#include "Controller.hpp"
#include "Control.hpp"
#include "Rope.hpp"
#include "Gyro.hpp"
#include <string>
#include "Debug.hpp"
#include <cstring>
#include "Time.hpp"
#include "math.h"
#include "Follow.hpp"
#include "MPU6050.hpp"
#include "Path.hpp"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t A_Rxdata_buff[ DATASIZE ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
uint8_t B_Rxdata_buff[ DATASIZE ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
uint8_t C_Rxdata_buff[ DATASIZE ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback( UART_HandleTypeDef* UartHandle )
{

	if( UartHandle == &huart4 )// data from B robot
	{
/*
		HAL_UART_Receive_IT(&huart4, (uint8_t*)Controller::controller_Rxdata, sizeof(Controller::controller_Rxdata));

		Controller* controller = new Controller();
		controller -> identify();
		delete controller;
*/

		HAL_UART_Receive_IT( &huart4, ( uint8_t* )B_Rxdata_buff, sizeof( B_Rxdata_buff ) );

		// C PSP
		if( B_Rxdata_buff[ 0 ] == ( uint8_t )E_data_type::done )
			Control::B_done_flag = true;



	}
	else if( UartHandle == &huart1 )// data from A robot
	{
		HAL_UART_Receive_IT(&huart1, (uint8_t*)A_Rxdata_buff, sizeof( A_Rxdata_buff ) );

		//B PSP
		if( A_Rxdata_buff[ 0 ] == ( uint8_t )E_data_type::A_pos )
		{
			Control* control = new Control();
			control -> decode_self_pos( &Follow::A_pos_x, &Follow::A_pos_y, A_Rxdata_buff );
			delete control;
		}
		//C PSP
		else if( A_Rxdata_buff[ 0 ] == ( uint8_t )E_data_type::done )
			Control::A_done_flag = true;





	}
	else if( UartHandle == &huart3 )// data from C robot
	{

		HAL_UART_Receive_IT(&huart3, (uint8_t*)C_Rxdata_buff, sizeof( C_Rxdata_buff ));


		//A and B PSP
		if( C_Rxdata_buff[ 0 ] == ( uint8_t )E_data_type::command )
			for( int i = 0; i < DATASIZE; i++ )
				Control::command[ i ] = C_Rxdata_buff[ i ];
		//A and B PSP
		else if( C_Rxdata_buff[ 0 ] == ( uint8_t )E_data_type::stop )
			Control::stop_flag = true;



	}

	for( int i = 0; i < DATASIZE; i++ )
	{
		A_Rxdata_buff[ i ] = 0;
		B_Rxdata_buff[ i ] = 0;
		C_Rxdata_buff[ i ] = 0;
	}



}

void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin )
{
	HGPIO* hgpio = new HGPIO();
	hgpio -> identify( GPIO_Pin );
	delete hgpio;

}

void HAL_TIM_PeriodElapsedCallback( TIM_HandleTypeDef* htim )
{
    if ( htim -> Instance == TIM3 )
    {
        __HAL_TIM_CLEAR_FLAG(&htim3, TIM_IT_UPDATE);
        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3)) Rope::over_flow_cnt_3--;
        else Rope::over_flow_cnt_3++;
    }
    else if( htim -> Instance == TIM4 )
    {
        __HAL_TIM_CLEAR_FLAG( &htim4, TIM_IT_UPDATE );
        if( __HAL_TIM_IS_TIM_COUNTING_DOWN( &htim4 ) ) Rope::over_flow_cnt_4--;
        else Rope::over_flow_cnt_4++;
    }


}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  Init_Move* init_move = new Init_Move();
  Control* control = new Control();
  Path* path = new Path();
  MPU6050* mpu6050 = new MPU6050();
  Self_Pos* self_pos = new Self_Pos();
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  MX_USART6_UART_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_I2C3_Init();
  MX_UART4_Init();
  MX_TIM7_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  /* USER CODE BEGIN 2 */
//  init_move -> init_move( ROBOT );
  HAL_TIM_Base_Start_IT( &htim6 );
  while( mpu6050 -> MPU6050_Init( &hi2c1 ) == true );
  HAL_TIM_Encoder_Start( &htim5, TIM_CHANNEL_ALL );
  HAL_TIM_Encoder_Start( &htim2, TIM_CHANNEL_ALL );


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  Debug::TTO_val( TIM5 -> CNT, "TIM5:", &huart2 );
	  Debug::TTO_val( TIM2 -> CNT, "TIM2:", &huart2 );

	  Debug::TTO_val( self_pos -> get_Self_Pos_X(), "X:", &huart2 );
	  Debug::TTO_val( self_pos -> get_Self_Pos_Y(), "Y:", &huart2 );
	  HAL_Delay( 100 );
/*
	  if( ROBOT == E_robot_name::A )
		  control -> control_A();
	  else if( ROBOT == E_robot_name::B )
		  control -> control_B();
	  else if( ROBOT == E_robot_name::C )
		  control -> control_C();


	  control -> reset_data();
*/
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 128;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */


  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
