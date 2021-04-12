/*
 * get_time.c
 *
 *  Created on: Apr 12, 2021
 *      Author: Ayato Yoshida
 */
#include "stdio.h"

char output_2[256];
uint32_t startTime;
uint32_t time;
double measure = 16011106;

void get_time()
{

	static int i = 0;


	i++;
	switch(i % 2)
	{
	case 1:
		CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
		DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
		startTime = DWT->CYCCNT;
		break;
	case 0:
		time = DWT->CYCCNT - startTime;
		double second = (double)time / measure;

		sprintf(output_2, "%lf\r\n", second);
		HAL_UART_Transmit(&huart2, (uint8_t*)output_2, sizeof(output_2), 100);

		break;
	}



}

