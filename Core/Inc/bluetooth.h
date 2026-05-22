#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_

#include "main.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

void Bluetooth_Init(void);
void Bluetooth_SendString(char *str);
void Bluetooth_SendDistance(float distance);

#endif /* INC_BLUETOOTH_H_ */
