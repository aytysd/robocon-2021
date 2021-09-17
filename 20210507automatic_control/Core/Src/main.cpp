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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Function.hpp"
#include "Infinity_command.hpp"
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
#include "Stay_Jump.hpp"
#include "Line.hpp"
#include "Jump.hpp"
#include "Control_C.hpp"
#include "Control_A.hpp"
#include "Control_B.hpp"
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
uint8_t A_Rxdata_buff = 0;
uint8_t B_Rxdata_buff = 0;
uint8_t C_Rxdata_buff = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback( UART_HandleTypeDef* UartHandle )
{

	static uint8_t A_Rxdata[ DATASIZE ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	static uint8_t B_Rxdata[ DATASIZE ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	static uint8_t C_Rxdata[ DATASIZE ] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	static bool A_Is_receiving = false;
	static bool B_Is_receiving = false;
	static bool C_Is_receiving = false;

	static uint8_t A_count = 0;
	static uint8_t B_count = 0;
	static uint8_t C_count = 0;


	if( UartHandle == &huart4 )
	{
		HAL_UART_Receive_IT(&huart4, (uint8_t*)Controller::controller_Rxdata, sizeof(Controller::controller_Rxdata));

		Controller* controller = new Controller();
		controller -> identify();
		delete controller;



	}
	else if( UartHandle == &huart5 )//data from B
	{

		HAL_UART_Receive_IT( &huart5, ( uint8_t* )&B_Rxdata_buff, sizeof( B_Rxdata_buff ) );


		if( ( ( B_Rxdata_buff & 0b10000000 ) >> 7 ) == true && B_Is_receiving == false )
		{
			for( int i = 0; i < DATASIZE; i++ )
				B_Rxdata[ i ] = 0;

			B_Rxdata_buff -= 0b10000000;
			B_Rxdata[ 0 ] = B_Rxdata_buff;

			B_Is_receiving = true;
			B_count = 1;

			return;

		}
		else if( ( ( B_Rxdata_buff & 0b01000000 ) >> 6 )== true && B_Is_receiving == false )
		{
			B_Rxdata_buff -= 0b01000000;
			B_Rxdata[ 7 ] = B_Rxdata_buff;

			B_count = 0;


		}
		else if( B_Is_receiving == true )
		{
			B_Rxdata[ B_count ] = B_Rxdata_buff;
			B_count++;

			if( B_count == 7 )
				B_Is_receiving = false;

			return;

		}





		//a or c PSP
		if( B_Rxdata[ 0 ] == ( uint8_t )E_data_type::B_pos )
		{
			Control* control = new Control();

			int16_t x;
			int16_t y;

			control -> decode_self_pos( &x, &y, B_Rxdata );

			Debug::TTO_val( x, "X:" );
			Debug::TTO_val( y, "Y:" );

			delete control;
		}

		// C PSP
		else if( B_Rxdata[ 0 ] == ( uint8_t )E_data_type::ready )
			Control_C::B_ready_flag = true;



		for( int i = 0; i < DATASIZE; i++ )
			Debug::TTO_val( B_Rxdata[ i ], "B_data:" );

	}
	else if( UartHandle == &huart1 )// data from A robot
	{
		HAL_UART_Receive_IT( &huart1, ( uint8_t* )&A_Rxdata_buff, sizeof( A_Rxdata_buff ) );


		if( ( ( ( A_Rxdata_buff & 0b10000000 ) >> 7 ) == true ) && ( A_Is_receiving == false ) )
		{
			for( int i = 0; i < DATASIZE; i++ )
				A_Rxdata[ i ] = 0;

			A_Rxdata_buff -= 0b10000000;
			A_Rxdata[ 0 ] = A_Rxdata_buff;

			A_Is_receiving = true;
			A_count = 1;

			return;

		}
		else if( ( ( A_Rxdata_buff & 0b01000000 ) >> 6 )== true && A_Is_receiving == false )
		{
			A_Rxdata_buff -= 0b01000000;
			A_Rxdata[ 7 ] = A_Rxdata_buff;

			A_count = 0;


		}
		else if( A_Is_receiving == true )
		{
			A_Rxdata[ A_count ] = A_Rxdata_buff;
			A_count++;

			if( A_count ==  7 )
				A_Is_receiving = false;

			return;

		}




		//B or C PSP
		if( A_Rxdata[ 0 ] == ( uint8_t )E_data_type::A_pos )
		{
			Control* control = new Control();
			control -> decode_self_pos( &Line::A_pos_x, &Line::A_pos_y, A_Rxdata );

			Debug::TTO_val( Line::A_pos_x, "X:" );
			Debug::TTO_val( Line::A_pos_y, "Y:" );

			delete control;
		}
		//C PSP
		else if( A_Rxdata[ 0 ] == ( uint8_t )E_data_type::ready )
			Control_C::A_ready_flag = true;



		for( int i = 0; i < DATASIZE; i++ )
			Debug::TTO_val( A_Rxdata[ i ], "A_data:" );


	}
	else if( UartHandle == &huart3 )// data from C robot
	{

		HAL_UART_Receive_IT( &huart3, ( uint8_t* )&C_Rxdata_buff, sizeof( C_Rxdata_buff ) );

		if( ( ( C_Rxdata_buff & 0b10000000 ) >> 7 ) == true && C_Is_receiving == false )
		{
			for( int i = 0; i < DATASIZE; i++ )
				C_Rxdata[ i ] = 0;

			C_Rxdata_buff -= 0b10000000;
			C_Rxdata[ 0 ] = C_Rxdata_buff;

			C_Is_receiving = true;
			C_count = 1;

			return;

		}
		else if( ( ( C_Rxdata_buff & 0b01000000 ) >> 6 ) == true && C_Is_receiving == false )
		{
			C_Rxdata_buff -= 0b01000000;
			C_Rxdata[ 7 ] = C_Rxdata_buff;

			C_count = 0;


		}
		else if( C_Is_receiving == true )
		{
			C_Rxdata[ C_count ] = C_Rxdata_buff;
			C_count++;

			if( C_count == 7 )
				C_Is_receiving = false;


			return;

		}

		//A and B PSP
		if( C_Rxdata[ 0 ] == ( uint8_t )E_data_type::command )
			for( int i = 0; i < 2; i++ )
				Control::command[ i ] = C_Rxdata[ i ];
		//A and B PSP
		else if( C_Rxdata[ 0 ] == ( uint8_t )E_data_type::stop )
			Control::stop_flag = true;
		else if( C_Rxdata[ 0 ] == ( uint8_t )E_data_type::A_start )
			Control_A::start_flag = true;
		else if( C_Rxdata[ 0 ] == ( uint8_t )E_data_type::B_start )
			Control_B::start_flag = true;
		else if( C_Rxdata[ 0 ] == ( uint8_t )E_data_type::test )//A and B PSP
		{
			if( C_Rxdata[ 1 ] == 10 )
				Init_Move::SBDBT_OK = true;
		}
		else if( C_Rxdata[ 0 ] == ( uint8_t )E_data_type::rope )
		{
			Rope* rope = new Rope();
			rope -> Encoder_val_RX( &Jump::rope, C_Rxdata );

			Debug::TTO_val( Jump::rope, "rope:" );
			delete rope;
		}

		for( int i = 0; i < DATASIZE; i++ )
			Debug::TTO_val( C_Rxdata[ i ], "C_data:" );


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
  Control_A* A = new Control_A();
  Control_B* B = new Control_B();
  Control_C* C = new Control_C();
  MPU6050* mpu6050 = new MPU6050();
  Self_Pos* self_pos = new Self_Pos();
  Rope* rope = new Rope();
  Function* function = new Function();
  Line* line = new Line();
  PWM* pwm = new PWM();
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
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_UART4_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */

#ifdef AUTO
  init_move -> init_move( ROBOT );
#else
  HAL_UART_Receive_IT( &huart4, ( uint8_t* )Controller::controller_Rxdata, sizeof( Controller::controller_Rxdata ) );
  if( robot != E_robot_name::C )
	  while( mpu6050 -> MPU6050_Init( &hi2c1 ) == true );
#endif


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
#ifdef AUTO

	  switch( ROBOT )
	  {
	  case E_robot_name::A:
		  A -> control_A();
		  break;
	  case E_robot_name::B:
		  B -> control_B();
		  break;
	  case E_robot_name::C:
		  C -> control_C();
		  break;
	  default:
		  break;
	  }

	  control -> reset_data();
#endif
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
