/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"
#include "stm32f411xe.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

/* USART2 init function */

void MX_USART2_UART_Init(void)
{


    // ENABLE CLOCK

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // PA2 -> USART2_TX
    // PA3 -> USART2_RX
    // AF7

    // Alternate Function mode

    GPIOA->MODER &= ~(3 << (2 * 2));
    GPIOA->MODER |=  (2 << (2 * 2));

    GPIOA->MODER &= ~(3 << (3 * 2));
    GPIOA->MODER |=  (2 << (3 * 2));

    // AF7

    GPIOA->AFR[0] &= ~(0xF << (2 * 4));
    GPIOA->AFR[0] |=  (7 << (2 * 4));

    GPIOA->AFR[0] &= ~(0xF << (3 * 4));
    GPIOA->AFR[0] |=  (7 << (3 * 4));

    // USART CONFIG

    // 84MHz / 115200

    USART2->BRR = 0x2D9;

    // Enable TX + RX

    USART2->CR1 |= USART_CR1_TE;
    USART2->CR1 |= USART_CR1_RE;

    // Enable USART

    USART2->CR1 |= USART_CR1_UE;
}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{
	    // ENABLE CLOCK

	    RCC->APB2ENR |= RCC_APB2ENR_USART6EN;

	    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	    // PC6 -> USART6_TX
	    // PC7 -> USART6_RX
	    // AF8

	    GPIOC->MODER &= ~(3 << (6 * 2));
	    GPIOC->MODER |=  (2 << (6 * 2));

	    GPIOC->MODER &= ~(3 << (7 * 2));
	    GPIOC->MODER |=  (2 << (7 * 2));

	    // AF8

	    GPIOC->AFR[0] &= ~(0xF << (6 * 4));
	    GPIOC->AFR[0] |=  (8 << (6 * 4));

	    GPIOC->AFR[0] &= ~(0xF << (7 * 4));
	    GPIOC->AFR[0] |=  (8 << (7 * 4));

	    // USART CONFIG

	    // 84MHz / 9600

	    USART6->BRR = 0x222E;

	    // Enable TX + RX

	    USART6->CR1 |= USART_CR1_TE;
	    USART6->CR1 |= USART_CR1_RE;

	    // Enable USART

	    USART6->CR1 |= USART_CR1_UE;

}
