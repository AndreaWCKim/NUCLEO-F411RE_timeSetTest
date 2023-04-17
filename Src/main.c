/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/

/* USER CODE BEGIN PTD */
char time[30];
char date[30];
char msg[30];
/* USER CODE END PTD */


/* Private define ------------------------------------------------------------*/

/* USER CODE BEGIN PD */


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  //SystemClock_Config();
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
  RTC_DateTypeDef sDate;
  RTC_TimeTypeDef sTime;

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	  if (sTime.Hours>=24){

		  sDate.Date = sDate.Date + sTime.Hours/24;
		  sTime.Hours= sTime.Hours%24;
		  HAL_RTC_SetTime(&hrtc,&sTime, RTC_FORMAT_BIN);
		  HAL_RTC_SetDate(&hrtc,&sDate, RTC_FORMAT_BIN);
	  }


      if (sDate.Date > checkMonth(sDate.Year,sDate.Month)){
	      sDate.Date = sDate.Date - checkMonth(sDate.Year,sDate.Month);
          //HAL_UART_Transmit(&huart2,(uint8_t *)msg,sizeof(msg),100);

		  if (sDate.Month < 12){
			  sDate.Month += 1;
			  }

		  else{
			   sDate.Month = 1;
			   sDate.Year += 1;
			  }
		  HAL_RTC_SetTime(&hrtc,&sTime, RTC_FORMAT_BIN);
		  HAL_RTC_SetDate(&hrtc,&sDate, RTC_FORMAT_BIN);
      }

	  sprintf(date,"DATE : %02d.%02d.%02d\t",sDate.Year,sDate.Month,sDate.Date);
	  sprintf(time,"TIME : %02d:%02d:%02d\r\n",sTime.Hours,sTime.Minutes,sTime.Seconds);
		  //HAL_RTC_SetTime(&hrtc,&sTime, RTC_FORMAT_BIN);
		  //HAL_RTC_SetDate(&hrtc,&sDate, RTC_FORMAT_BIN);
		  //HAL_UART_Transmit(&huart2,(uint8_t *) msg,sizeof(msg),100);
	  HAL_UART_Transmit(&huart2,(uint8_t *) date,sizeof(date),100);
	  HAL_UART_Transmit(&huart2,(uint8_t *) time,sizeof(time),100);


	  HAL_Delay(1000);
}





      /*
	  if ((sTime.Hours>=24) || (sDate.Date > checkMonth(sDate.Year,sDate.Month))){

		  sDate.Date = sDate.Date + sTime.Hours/24;
		  sTime.Hours= sTime.Hours%24;
		  if (sDate.Date > checkMonth(sDate.Year,sDate.Month)){
			  sDate.Date = sDate.Date - checkMonth(sDate.Year,sDate.Month);

			  if (sDate.Month < 12){
				  sDate.Month += 1;
			  }
			  else{
				  sDate.Month = 1;
				  sDate.Year += 1;
			  }

		  }



	      sprintf(date,"DATE : %02d.%02d.%02d\t",sDate.Year,sDate.Month,sDate.Date);
		  sprintf(time,"TIME : %02d:%02d:%02d\r\n",sTime.Hours,sTime.Minutes,sTime.Seconds);
		  //HAL_RTC_SetTime(&hrtc,&sTime, RTC_FORMAT_BIN);
		  //HAL_RTC_SetDate(&hrtc,&sDate, RTC_FORMAT_BIN);
		  //HAL_UART_Transmit(&huart2,(uint8_t *) msg,sizeof(msg),100);
		  HAL_UART_Transmit(&huart2,(uint8_t *) date,sizeof(date),100);
		  HAL_UART_Transmit(&huart2,(uint8_t *) time,sizeof(time),100);
		  HAL_Delay(1000);
	  }

	  else {


      sprintf(date,"DATE : %02d.%02d.%02d\t",sDate.Year,sDate.Month,sDate.Date);
	  sprintf(time,"TIME : %02d:%02d:%02d\r\n",sTime.Hours,sTime.Minutes,sTime.Seconds);
	  //HAL_RTC_SetTime(&hrtc,&sTime, RTC_FORMAT_BIN);
	  //HAL_RTC_SetDate(&hrtc,&sDate, RTC_FORMAT_BIN);


	  HAL_UART_Transmit(&huart2,(uint8_t *) date,sizeof(date),100);
	  HAL_UART_Transmit(&huart2,(uint8_t *) time,sizeof(time),100);
	  HAL_Delay(1000);
	  */

    /* USER CODE END WHILE */



    /* USER CODE BEGIN 3 */

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int checkMonth(int year,int month){

	int maxDay = 0;
	int isLeap = 0;
	int tYear = year + 2000;

	if (tYear % 400 == 0){
		isLeap = 1;
	}
	else if (tYear % 100 == 0){
		isLeap = 0;
	}
	else if (tYear % 4 == 0){
		isLeap = 1;
	}
	else{
			isLeap = 0;
		}

	if (isLeap ==0){
	switch (month){

	case 2 : maxDay = 28;break;

	case 4 : maxDay = 30;break;

	case 6 : maxDay = 30;break;


	case 9: maxDay = 30;break;

	case 11: maxDay = 30;break;

	default: maxDay = 31 ; break;
	    }
	}
	else if (isLeap ==1){
		switch (month){

		case 2 : maxDay = 29;break;

		case 4 : maxDay = 30;break;

		case 6 : maxDay = 30;break;


		case 9 : maxDay = 30;break;

		case 11 : maxDay = 30;break;

		default : maxDay = 31;break;
	    }
	}
	return maxDay;
}


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
