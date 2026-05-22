#ifndef __HCSR04_H
#define __HCSR04_H

#include "main.h"

// Khởi tạo module (nếu cần)
void HCSR04_Init(void);

// Đo khoảng cách, trả về đơn vị cm
float HCSR04_Read(void);

#endif
