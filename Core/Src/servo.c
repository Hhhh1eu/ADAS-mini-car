#include "servo.h"
#include "tim.h"

void Servo_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    Servo_SetAngle(90);   // nhìn thẳng
    HAL_Delay(500);
}

void Servo_SetAngle(uint8_t angle)
{
    uint16_t pulse;

    if (angle > 180)
        angle = 180;

    // 500us -> 0°
    // 1500us -> 90°
    // 2500us -> 180°
    pulse = 500 + (angle * 2000) / 180;

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pulse);
}
