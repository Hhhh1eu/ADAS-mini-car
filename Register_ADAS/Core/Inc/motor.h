#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"
#include "tim.h"

#include "stm32f411xe.h"

#include <stdint.h>

// ====================================
// INIT
// ====================================

void Motor_Init(void);

// ====================================
// SPEED
// ====================================

void Motor_SetLeftSpeed(uint8_t percent);

void Motor_SetRightSpeed(uint8_t percent);

void Motor_SetSpeed(uint8_t left_percent,
                    uint8_t right_percent);

// ====================================
// DIRECTION
// ====================================

void Motor_Forward(void);

void Motor_Backward(void);

void Motor_TurnLeft(void);

void Motor_TurnRight(void);

void Motor_Stop(void);

#endif /* INC_MOTOR_H_ */
