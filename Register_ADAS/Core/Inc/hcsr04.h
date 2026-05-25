#ifndef INC_HCSR04_H_
#define INC_HCSR04_H_

#include "main.h"

#include "stm32f411xe.h"

#include <stdint.h>

// ====================================
// HC-SR04
// ====================================

void HCSR04_Init(void);

float HCSR04_Read(void);

#endif /* INC_HCSR04_H_ */
