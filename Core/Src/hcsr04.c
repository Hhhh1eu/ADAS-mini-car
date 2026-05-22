#include "hcsr04.h"

#define HCSR04_SAMPLES      5
#define HCSR04_TIMEOUT_MS   100
#define HCSR04_SCALE        72  // Hệ số hiệu chỉnh dựa vào đo thực nghiệm

static float HCSR04_ReadOnce(void)
{
    uint32_t count = 0;
    uint32_t timeout;
    float distance;

    // Đưa TRIG xuống thấp
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_Delay(1);

    // Tạo xung TRIG ~10 us
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
    for (volatile uint32_t i = 0; i < 100; i++);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);

    // Chờ ECHO lên mức cao
    timeout = HAL_GetTick();
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
    {
        if (HAL_GetTick() - timeout > HCSR04_TIMEOUT_MS)
        {
            return -1.0f;
        }
    }

    // Đếm thời gian ECHO ở mức cao
    timeout = HAL_GetTick();
    count = 0;

    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
    {
        count++;

        if (HAL_GetTick() - timeout > HCSR04_TIMEOUT_MS)
        {
            return -1.0f;
        }
    }

    // Quy đổi sang cm
    distance = count / HCSR04_SCALE;

    // Kiểm tra phạm vi hợp lệ
    if (distance < 2.0f || distance > 400.0f)
    {
        return -1.0f;
    }

    return distance;
}

void HCSR04_Init(void)
{
}

float HCSR04_Read(void)
{
    float sum = 0.0f;
    int valid_count = 0;

    for (int i = 0; i < HCSR04_SAMPLES; i++)
    {
        float d = HCSR04_ReadOnce();

        if (d > 0)
        {
            sum += d;
            valid_count++;
        }

        HAL_Delay(20); // Chờ giữa các lần đo
    }

    if (valid_count == 0)
    {
        return -1.0f;
    }

    return sum / valid_count;
}
