#include "bluetooth.h"

#include <string.h>
#include <stdio.h>

// ====================================
// INIT
// ====================================

void Bluetooth_Init(void)
{
}

// ====================================
// SEND 1 CHAR
// ====================================

void Bluetooth_SendChar(char c)
{
    // Wait TX empty
    while(!(USART6->SR & USART_SR_TXE));

    USART6->DR = c;
}

// ====================================
// SEND STRING
// ====================================

void Bluetooth_SendString(char *str)
{
    while(*str)
    {
        Bluetooth_SendChar(*str);

        str++;
    }
}

// ====================================
// CHECK RX AVAILABLE
// ====================================

uint8_t Bluetooth_Available(void)
{
    return (USART6->SR & USART_SR_RXNE);
}

// ====================================
// READ CHAR
// ====================================

char Bluetooth_ReadChar(void)
{
    while(!(USART6->SR & USART_SR_RXNE));

    return USART6->DR;
}

// ====================================
// SEND DISTANCE
// ====================================

void Bluetooth_SendDistance(float distance)
{
    char buffer[50];

    sprintf(buffer,
            "Distance: %.1f cm\r\n",
            distance);

    Bluetooth_SendString(buffer);
}
