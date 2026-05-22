#include "motor.h"

// TIM3_CH1 (PA6) -> MOTOR_LEFT_EN
// TIM3_CH2 (PA7) -> MOTOR_RIGHT_EN
// PB0  -> MOTOR_LEFT_IN1
// PB1  -> MOTOR_LEFT_IN2
// PB10 -> MOTOR_RIGHT_IN1
// PB12 -> MOTOR_RIGHT_IN2

#define PWM_MAX 999

// Ham chuyen gia tri % toc do thanh gia tri CCR PWM
static uint32_t PercentToCompare(uint8_t percent)
{
    if (percent > 100)
        percent = 100;

    return (PWM_MAX * percent) / 100;
}

// Khởi tạo PWM cho 2 motor
void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // Motor trái
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // Motor phải

    Motor_Stop();
}

// Điều chỉnh tốc độ (0-100%)
void Motor_SetLeftSpeed(uint8_t percent)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,
                          PercentToCompare(percent));
}

void Motor_SetRightSpeed(uint8_t percent)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,
                          PercentToCompare(percent));
}

void Motor_SetSpeed(uint8_t left_percent, uint8_t right_percent)
{
    Motor_SetLeftSpeed(left_percent);
    Motor_SetRightSpeed(right_percent);
}

// Điều khiển hướng
void Motor_Backward(void)
{
    // Motor trái lui
    HAL_GPIO_WritePin(MOTOR_LEFT_IN1_GPIO_Port,
                      MOTOR_LEFT_IN1_Pin,
                      GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_LEFT_IN2_GPIO_Port,
                      MOTOR_LEFT_IN2_Pin,
                      GPIO_PIN_RESET);

    // Motor phải lui
    HAL_GPIO_WritePin(MOTOR_RIGHT_IN1_GPIO_Port,
                      MOTOR_RIGHT_IN1_Pin,
                      GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_IN2_GPIO_Port,
                      MOTOR_RIGHT_IN2_Pin,
                      GPIO_PIN_RESET);
}

void Motor_Forward(void)
{
    // Motor trái tien
    HAL_GPIO_WritePin(MOTOR_LEFT_IN1_GPIO_Port,
                      MOTOR_LEFT_IN1_Pin,
                      GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_LEFT_IN2_GPIO_Port,
                      MOTOR_LEFT_IN2_Pin,
                      GPIO_PIN_SET);

    // Motor phải tien
    HAL_GPIO_WritePin(MOTOR_RIGHT_IN1_GPIO_Port,
                      MOTOR_RIGHT_IN1_Pin,
                      GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_IN2_GPIO_Port,
                      MOTOR_RIGHT_IN2_Pin,
                      GPIO_PIN_SET);
}

void Motor_TurnLeft(void)
{
	 // Bánh trái lùi
    HAL_GPIO_WritePin(MOTOR_LEFT_IN1_GPIO_Port, MOTOR_LEFT_IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_LEFT_IN2_GPIO_Port, MOTOR_LEFT_IN2_Pin, GPIO_PIN_RESET);

    // Bánh phải tiến
    HAL_GPIO_WritePin(MOTOR_RIGHT_IN1_GPIO_Port, MOTOR_RIGHT_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_IN2_GPIO_Port, MOTOR_RIGHT_IN2_Pin, GPIO_PIN_SET);

    Motor_SetLeftSpeed(30);
    Motor_SetRightSpeed(70);
}

void Motor_TurnRight(void)
{
	// Bánh trái tiến
	    HAL_GPIO_WritePin(MOTOR_LEFT_IN1_GPIO_Port, MOTOR_LEFT_IN1_Pin, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(MOTOR_LEFT_IN2_GPIO_Port, MOTOR_LEFT_IN2_Pin, GPIO_PIN_SET);

	    // Bánh phải lùi
	    HAL_GPIO_WritePin(MOTOR_RIGHT_IN1_GPIO_Port, MOTOR_RIGHT_IN1_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(MOTOR_RIGHT_IN2_GPIO_Port, MOTOR_RIGHT_IN2_Pin, GPIO_PIN_RESET);

	    Motor_SetLeftSpeed(70);
	    Motor_SetRightSpeed(30);
}

void Motor_Stop(void)
{
    // Tắt PWM
    Motor_SetSpeed(0, 0);

    // Đưa tất cả chân điều khiển về 0
    HAL_GPIO_WritePin(MOTOR_LEFT_IN1_GPIO_Port,
                      MOTOR_LEFT_IN1_Pin,
                      GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_LEFT_IN2_GPIO_Port,
                      MOTOR_LEFT_IN2_Pin,
                      GPIO_PIN_RESET);

    HAL_GPIO_WritePin(MOTOR_RIGHT_IN1_GPIO_Port,
                      MOTOR_RIGHT_IN1_Pin,
                      GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_RIGHT_IN2_GPIO_Port,
                      MOTOR_RIGHT_IN2_Pin,
                      GPIO_PIN_RESET);
}
