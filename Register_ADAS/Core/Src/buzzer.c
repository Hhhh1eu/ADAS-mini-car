#include "buzzer.h"

// PA8 -> Buzzer

// ====================================
// BUZZER ON
// ====================================

void Buzzer_On(void)
{
    GPIOA->ODR |= (1 << 8);
}

// ====================================
// BUZZER OFF
// ====================================

void Buzzer_Off(void)
{
    GPIOA->ODR &= ~(1 << 8);
}

// ====================================
// BUZZER BEEP
// ====================================

void Buzzer_Beep(uint32_t ms)
{
    Buzzer_On();

    HAL_Delay(ms);

    Buzzer_Off();
}
