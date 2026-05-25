#include "hcsr04.h"

#define HCSR04_SAMPLES      5
#define HCSR04_TIMEOUT_MS   100

#define HCSR04_SCALE        144

// READ ONE SAMPLE

static float HCSR04_ReadOnce(void)
{
    uint32_t count = 0;

    uint32_t timeout;

    float distance;

    // TRIG LOW

    GPIOA->ODR &= ~(1 << 0);

    HAL_Delay(1);

    // TRIG HIGH ~10us

    GPIOA->ODR |= (1 << 0);

    for(volatile uint32_t i = 0; i < 100; i++);

    GPIOA->ODR &= ~(1 << 0);

    // WAIT ECHO HIGH

    timeout = HAL_GetTick();

    while(!(GPIOA->IDR & (1 << 1)))
    {
        if((HAL_GetTick() - timeout)
            > HCSR04_TIMEOUT_MS)
        {
            return -1.0f;
        }
    }

    // COUNT ECHO HIGH TIME

    timeout = HAL_GetTick();

    count = 0;

    while(GPIOA->IDR & (1 << 1))
    {
        count++;

        if((HAL_GetTick() - timeout)
            > HCSR04_TIMEOUT_MS)
        {
            return -1.0f;
        }
    }

    // CONVERT TO CM

    distance = count / HCSR04_SCALE;

    // VALID RANGE

    if(distance < 2.0f)
    {
        return -1.0f;
    }
    if (distance > 400.0f)
    {
    	return 999.0f;
    }
    return distance;
}

// INIT

void HCSR04_Init(void)
{
}

// READ FILTERED DISTANCE

float HCSR04_Read(void)
{
    float sum = 0.0f;

    int valid_count = 0;

    for(int i = 0; i < HCSR04_SAMPLES; i++)
    {
        float d = HCSR04_ReadOnce();

        if(d > 0)
        {
            sum += d;

            valid_count++;
        }

        HAL_Delay(20);
    }

    if(valid_count == 0)
    {
        return -1.0f;
    }

    return sum / valid_count;
}
