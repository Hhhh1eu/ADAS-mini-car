#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_

#include "main.h"

#include "usart.h"

#include "stm32f411xe.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

// ====================================
// INIT
// ====================================

void Bluetooth_Init(void);

// ====================================
// SEND
// ====================================

void Bluetooth_SendChar(char c);

void Bluetooth_SendString(char *str);

void Bluetooth_SendDistance(float distance);

// ====================================
// RECEIVE
// ====================================

uint8_t Bluetooth_Available(void);

char Bluetooth_ReadChar(void);

#endif /* INC_BLUETOOTH_H_ */
