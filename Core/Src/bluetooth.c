#include "bluetooth.h"

void Bluetooth_Init(void)
{
}

void Bluetooth_SendString(char *str)
{
   HAL_UART_Transmit(&huart6,
                      (uint8_t *)str,
                      strlen(str),
                      100);
}

void Bluetooth_SendDistance(float distance)
{
    char buffer[50];

    sprintf(buffer, "Distance: %.1f cm\r\n", distance);

    Bluetooth_SendString(buffer);
}
