/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hcsr04.h"
#include "led.h"
#include "buzzer.h"
#include <stdio.h>
#include "motor.h"
#include "lcd_i2c.h"
#include "servo.h"

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE BEGIN 0 */

int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

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
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
  Motor_Init();
  HCSR04_Init();
  Servo_Init();
  LCD_Init();

  LCD_Clear();

  LCD_SetCursor(0, 0);
  LCD_Print("ADAS System");
  LCD_SetCursor(0, 1);
  LCD_Print("Starting...");
  HAL_Delay(1000);

  LCD_Clear();

  float distance;

  const float speed_ms = 0.7f;
  const float reaction_time = 0.6f;
  const float brake_accel = 1.5f;

uint32_t command_timer = 0;

  float d_safe;

  char buffer[17];

  uint8_t bt_data;
  char command = 'X';
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
    {
	  // =========================
	  // Nhận dữ liệu Bluetooth
	  // =========================

	  if (HAL_UART_Receive(&huart6, &bt_data, 1, 10) == HAL_OK)
	  {
	      command = bt_data;
		command_timer = HAL_GetTick();
		  
	      printf("CMD: %c\r\n", command);
	  }
		
		if (HAL_GetTick() - command_timer > 300)
	  {
	      command = 'X';
	  }
		
        // Đọc khoảng cách
        distance = HCSR04_Read();

        //Tính khoảng cách an toàn
        d_safe = (speed_ms * reaction_time)
                  + ((speed_ms * speed_ms) / (2.0f * brake_accel));

           d_safe *= 100.0f; // đổi sang cm

        // =========================
        // Trường hợp lỗi cảm biến
        // =========================
        if (distance < 0)
        {
            printf("Sensor Error\r\n");

            LCD_SetCursor(0, 0);
            LCD_Print("Sensor Error    ");

            LCD_SetCursor(0, 1);
            LCD_Print("Check HC-SR04   ");

            LED_Off();
            Buzzer_Off();
            Motor_Stop();

            HAL_Delay(200);
            continue;
        }

        // =========================
        // UART Debug
        // =========================
        printf("Distance = %.2f cm | Safe = %.2f cm\r\n", distance, d_safe);

        // =========================
        // LCD dòng 1: khoảng cách
        // =========================
        snprintf(buffer, sizeof(buffer), "D:%3.0f S:%3.0f", distance, d_safe);

        LCD_SetCursor(0, 0);
        LCD_Print("                ");   // xóa dòng

        LCD_SetCursor(0, 0);
        LCD_Print(buffer);

        // =====================================
        // SAFE
        // =====================================

        if (distance > d_safe + 45.0f)
        {
            LED_Off();
            Buzzer_Off();

            LCD_SetCursor(0,1);
            LCD_Print("SAFE            ");

            switch(command)
                    {
                        case 'W':
                        case 'w':

                            Motor_Forward();
                            Motor_SetSpeed(70, 70);

                            break;

                        case 'S':
                        case 's':

                            Motor_Backward();
                            Motor_SetSpeed(70, 70);

                            break;

                        case 'A':
                        case 'a':

                        	Motor_TurnLeft();

                            break;

                        case 'D':
                        case 'd':

                        	Motor_TurnRight();

                            break;

                        case 'X':
                        case 'x':

                            Motor_Stop();

                            break;

                        default:

                            Motor_Stop();

                            break;
                    }
                }

        // =====================================
        // WARNING
        // =====================================

        else if (distance > d_safe)
        {
            LED_On();
            Buzzer_On();
        	HAL_Delay(50);
        	Buzzer_Off();

            LCD_SetCursor(0,1);
            LCD_Print("WARNING         ");

            // Giảm tốc nhưng vẫn điều khiển được
                    switch(command)
                    {
                        case 'W':
                        case 'w':

                            Motor_Forward();
                            Motor_SetSpeed(45,45);

                            break;

                        case 'S':
                        case 's':

                            Motor_Backward();
                            Motor_SetSpeed(45,45);

                            break;

                        case 'A':
                        case 'a':

                        	Motor_TurnLeft();

                            break;

                        case 'D':
                        case 'd':

                        	Motor_TurnRight();

                            break;

                        default:

                            Motor_Stop();

                            break;
                    }
        }

        // =====================================
        // DANGER
        // =====================================

        else
        {
        	LED_Toggle();

            Buzzer_On();

            LCD_SetCursor(0,1);
            LCD_Print("DANGER          ");

            switch(command)
                {
                    // =====================
                    // CẤM TIẾN
                    // =====================

                    case 'W':
                    case 'w':

                        Motor_Stop();

                        break;

                    // =====================
                    // CHO PHÉP LÙI
                    // =====================

                    case 'S':
                    case 's':

                        Motor_Backward();
                        Motor_SetSpeed(45,45);

                        break;

                    // =====================
                    // RẼ TRÁI
                    // =====================

                    case 'A':
                    case 'a':

                        Motor_Forward();

                        Motor_SetLeftSpeed(20);
                        Motor_SetRightSpeed(45);

                        break;

                    // =====================
                    // RẼ PHẢI
                    // =====================

                    case 'D':
                    case 'd':

                        Motor_Forward();

                        Motor_SetLeftSpeed(45);
                        Motor_SetRightSpeed(20);

                        break;

                    // =====================
                    // STOP
                    // =====================

                    case 'X':
                    case 'x':

                        Motor_Stop();

                        break;

                    // =====================
                    // DEFAULT
                    // =====================

                    default:

                        Motor_Stop();

                        break;
                }
        }

        HAL_Delay(10);
    }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
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
