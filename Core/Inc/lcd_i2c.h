#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_

#include "main.h"
#include "i2c.h"
#include <stdint.h>

/* Địa chỉ I2C của module PCF8574
 * Thường là 0x27 hoặc 0x3F.
 * HAL dùng địa chỉ 8-bit, nên cần dịch trái 1 bit.
 */
#define LCD_I2C_ADDR (0x27 << 1)

/* Các bit điều khiển trên PCF8574 */
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_RS        0x01

/* API công khai */
void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t col, uint8_t row);
void LCD_Print(char *str);

#endif /* INC_LCD_I2C_H_ */
