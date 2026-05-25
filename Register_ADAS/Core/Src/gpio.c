/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"
#include "stm32f411xe.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

	// ENABLE GPIO CLOCK

	    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	    // PA0 -> HCSR04_TRIG OUTPUT

	    GPIOA->MODER &= ~(3 << (0 * 2));
	    GPIOA->MODER |=  (1 << (0 * 2));

	    // PA5 -> LED OUTPUT

	    GPIOA->MODER &= ~(3 << (5 * 2));
	    GPIOA->MODER |=  (1 << (5 * 2));

	    // PA8 -> BUZZER OUTPUT

	    GPIOA->MODER &= ~(3 << (8 * 2));
	    GPIOA->MODER |=  (1 << (8 * 2));

	    // PA1 -> HCSR04_ECHO INPUT

	    GPIOA->MODER &= ~(3 << (1 * 2));

	    // PB0 -> MOTOR_LEFT_IN1 OUTPUT

	    GPIOB->MODER &= ~(3 << (0 * 2));
	    GPIOB->MODER |=  (1 << (0 * 2));

	    // PB1 -> MOTOR_LEFT_IN2 OUTPUT

	    GPIOB->MODER &= ~(3 << (1 * 2));
	    GPIOB->MODER |=  (1 << (1 * 2));

	    // PB10 -> MOTOR_RIGHT_IN1 OUTPUT

	    GPIOB->MODER &= ~(3 << (10 * 2));
	    GPIOB->MODER |=  (1 << (10 * 2));

	    // PB12 -> MOTOR_RIGHT_IN2 OUTPUT

	    GPIOB->MODER &= ~(3 << (12 * 2));
	    GPIOB->MODER |=  (1 << (12 * 2));

	    // RESET OUTPUTS

	    GPIOA->ODR &= ~(1 << 0);
	    GPIOA->ODR &= ~(1 << 5);
	    GPIOA->ODR &= ~(1 << 8);

	    GPIOB->ODR &= ~(1 << 0);
	    GPIOB->ODR &= ~(1 << 1);
	    GPIOB->ODR &= ~(1 << 10);
	    GPIOB->ODR &= ~(1 << 12);
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
