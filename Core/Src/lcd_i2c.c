#include "lcd_i2c.h"
#include <string.h>

/* Bảng địa chỉ DDRAM cho từng dòng */
static const uint8_t row_offsets[] = {0x00, 0x40};

/* Gửi 1 byte ra PCF8574 */
static void LCD_WriteI2C(uint8_t data)
{
    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, &data, 1, HAL_MAX_DELAY);
}

/* Tạo xung EN để LCD chốt dữ liệu */
static void LCD_PulseEnable(uint8_t data)
{
    LCD_WriteI2C(data | LCD_ENABLE);
    HAL_Delay(1);

    LCD_WriteI2C(data & ~LCD_ENABLE);
    HAL_Delay(1);
}

/* Gửi 4 bit (nibble) */
static void LCD_Write4Bits(uint8_t nibble)
{
    LCD_WriteI2C(nibble | LCD_BACKLIGHT);
    LCD_PulseEnable(nibble | LCD_BACKLIGHT);
}

/* Gửi lệnh (RS = 0) */
static void LCD_SendCommand(uint8_t cmd)
{
    LCD_Write4Bits(cmd & 0xF0);          // 4 bit cao
    LCD_Write4Bits((cmd << 4) & 0xF0);   // 4 bit thấp
}

/* Gửi dữ liệu (RS = 1) */
static void LCD_SendData(uint8_t data)
{
    LCD_Write4Bits((data & 0xF0) | LCD_RS);
    LCD_Write4Bits(((data << 4) & 0xF0) | LCD_RS);
}

/* Khởi tạo LCD ở chế độ 4-bit */
void LCD_Init(void)
{
    HAL_Delay(50);   // Chờ LCD ổn định sau khi cấp nguồn

    /* Trình tự khởi tạo chuẩn cho HD44780 */
    LCD_Write4Bits(0x30);
    HAL_Delay(5);

    LCD_Write4Bits(0x30);
    HAL_Delay(1);

    LCD_Write4Bits(0x30);
    HAL_Delay(1);

    LCD_Write4Bits(0x20);   // Chuyển sang 4-bit mode
    HAL_Delay(1);

    /* Function Set: 4-bit, 2 dòng, font 5x8 */
    LCD_SendCommand(0x28);

    /* Display ON, Cursor OFF, Blink OFF */
    LCD_SendCommand(0x0C);

    /* Entry Mode: tự tăng địa chỉ, không dịch màn hình */
    LCD_SendCommand(0x06);

    /* Xóa màn hình */
    LCD_Clear();
}

/* Xóa màn hình */
void LCD_Clear(void)
{
    LCD_SendCommand(0x01);
    HAL_Delay(2);
}

/* Đặt vị trí con trỏ */
void LCD_SetCursor(uint8_t col, uint8_t row)
{
    if (row > 1)
        row = 1;

    LCD_SendCommand(0x80 | (col + row_offsets[row]));
}

/* In chuỗi ký tự */
void LCD_Print(char *str)
{
    while (*str)
    {
        LCD_SendData((uint8_t)(*str));
        str++;
    }
}
