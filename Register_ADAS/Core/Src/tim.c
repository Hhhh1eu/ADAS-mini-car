/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
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
#include "tim.h"
#include "stm32f411xe.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim3;

/* TIM3 init function */
void MX_TIM3_Init(void)
{
	    // ENABLE CLOCK

	    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	    // PA6 -> TIM3_CH1
	    // PA7 -> TIM3_CH2
	    // AF2

	    // MODER = Alternate Function

	    GPIOA->MODER &= ~(3 << (6 * 2));
	    GPIOA->MODER |=  (2 << (6 * 2));

	    GPIOA->MODER &= ~(3 << (7 * 2));
	    GPIOA->MODER |=  (2 << (7 * 2));

	    // AFRL AF2

	    GPIOA->AFR[0] &= ~(0xF << (6 * 4));
	    GPIOA->AFR[0] |=  (2 << (6 * 4));

	    GPIOA->AFR[0] &= ~(0xF << (7 * 4));
	    GPIOA->AFR[0] |=  (2 << (7 * 4));

	    // TIMER CONFIG

	    // 84MHz / (83+1) = 1MHz

	    TIM3->PSC = 83;

	    // PWM frequency

	    TIM3->ARR = 999;

	    // PWM MODE CH1

	    TIM3->CCMR1 &= ~(7 << 4);

	    TIM3->CCMR1 |= (6 << 4);

	    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;

	    // PWM MODE CH2

	    TIM3->CCMR1 &= ~(7 << 12);

	    TIM3->CCMR1 |= (6 << 12);

	    TIM3->CCMR1 |= TIM_CCMR1_OC2PE;

	    // ENABLE CHANNEL

	    TIM3->CCER |= TIM_CCER_CC1E;

	    TIM3->CCER |= TIM_CCER_CC2E;

	    // INITIAL DUTY

	    TIM3->CCR1 = 0;

	    TIM3->CCR2 = 0;

	    // ENABLE AUTO-RELOAD

	    TIM3->CR1 |= TIM_CR1_ARPE;

	    // UPDATE EVENT

	    TIM3->EGR |= TIM_EGR_UG;

	    // START TIMER

	    TIM3->CR1 |= TIM_CR1_CEN;
}
