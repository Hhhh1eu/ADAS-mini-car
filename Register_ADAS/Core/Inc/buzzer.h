#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

#include "stm32f411xe.h"

#include <stdint.h>

// ====================================
// BUZZER CONTROL
// ====================================

void Buzzer_On(void);

void Buzzer_Off(void);

void Buzzer_Beep(uint32_t ms);

#endif /* INC_BUZZER_H_ */
