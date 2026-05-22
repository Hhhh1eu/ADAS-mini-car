#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"
#include "tim.h"
#include <stdint.h>

// Khởi tạo PWM cho 2 motor
void Motor_Init(void);

// Điều chỉnh tốc độ (0-100%)
void Motor_SetLeftSpeed(uint8_t percent);
void Motor_SetRightSpeed(uint8_t percent);
void Motor_SetSpeed(uint8_t left_percent, uint8_t right_percent);

// Điều khiển hướng
void Motor_Forward(void);
void Motor_Backward(void);
void Motor_TurnLeft(void);
void Motor_TurnRight(void);
void Motor_Stop(void);

#endif /* INC_MOTOR_H_ */
