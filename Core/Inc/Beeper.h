#ifndef __BEEPER_H
#define __BEEPER_H

#include "stm32f1xx_hal.h"  // 包含 HAL 库头文件
#include "gpio.h"
void Beeper_On(void);
void Beeper_Off(void);
void Beeper_Toggle(void);
void Beeper_Beep(uint16_t ms);
#endif
