#include "motor.h"

// TIM3_CH1 (PA6) -> MOTOR_LEFT_EN
// TIM3_CH2 (PA7) -> MOTOR_RIGHT_EN

// PB0  -> MOTOR_LEFT_IN1
// PB1  -> MOTOR_LEFT_IN2

// PB10 -> MOTOR_RIGHT_IN1
// PB12 -> MOTOR_RIGHT_IN2

#define PWM_MAX 999

// ====================================
// Convert % speed -> CCR value
// ====================================

static uint32_t PercentToCompare(uint8_t percent)
{
    if(percent > 100)
    {
        percent = 100;
    }

    return (PWM_MAX * percent) / 100;
}

// ====================================
// INIT PWM
// ====================================

void Motor_Init(void)
{
    Motor_Stop();
}

// ====================================
// SPEED CONTROL
// ====================================

void Motor_SetLeftSpeed(uint8_t percent)
{
    TIM3->CCR1 = PercentToCompare(percent);
}

void Motor_SetRightSpeed(uint8_t percent)
{
    TIM3->CCR2 = PercentToCompare(percent);
}

void Motor_SetSpeed(uint8_t left_percent,
                    uint8_t right_percent)
{
    Motor_SetLeftSpeed(left_percent);

    Motor_SetRightSpeed(right_percent);
}

// ====================================
// BACKWARD
// ====================================

void Motor_Backward(void)
{
    // LEFT MOTOR BACKWARD
    GPIOB->ODR |=  (1 << 0);
    GPIOB->ODR &= ~(1 << 1);

    // RIGHT MOTOR BACKWARD
    GPIOB->ODR |=  (1 << 10);
    GPIOB->ODR &= ~(1 << 12);
}

// ====================================
// FORWARD
// ====================================

void Motor_Forward(void)
{
    // LEFT MOTOR FORWARD
    GPIOB->ODR &= ~(1 << 0);
    GPIOB->ODR |=  (1 << 1);

    // RIGHT MOTOR FORWARD
    GPIOB->ODR &= ~(1 << 10);
    GPIOB->ODR |=  (1 << 12);
}

// ====================================
// TURN LEFT
// ====================================

void Motor_TurnLeft(void)
{
    // LEFT MOTOR BACKWARD
    GPIOB->ODR |=  (1 << 0);
    GPIOB->ODR &= ~(1 << 1);

    // RIGHT MOTOR FORWARD
    GPIOB->ODR &= ~(1 << 10);
    GPIOB->ODR |=  (1 << 12);

    Motor_SetLeftSpeed(30);

    Motor_SetRightSpeed(70);
}

// ====================================
// TURN RIGHT
// ====================================

void Motor_TurnRight(void)
{
    // LEFT MOTOR FORWARD
    GPIOB->ODR &= ~(1 << 0);
    GPIOB->ODR |=  (1 << 1);

    // RIGHT MOTOR BACKWARD
    GPIOB->ODR |=  (1 << 10);
    GPIOB->ODR &= ~(1 << 12);

    Motor_SetLeftSpeed(70);

    Motor_SetRightSpeed(30);
}

// ====================================
// STOP
// ====================================

void Motor_Stop(void)
{
    // Stop PWM
    Motor_SetSpeed(0,0);

    // Clear direction pins

    GPIOB->ODR &= ~(1 << 0);
    GPIOB->ODR &= ~(1 << 1);

    GPIOB->ODR &= ~(1 << 10);
    GPIOB->ODR &= ~(1 << 12);
}
