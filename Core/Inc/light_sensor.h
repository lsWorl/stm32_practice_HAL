#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H
#include "adc.h"
#include "gpio.h"
#include "stm32f1xx_hal.h"  // 包含 HAL 库头文件

// 光照强度等级定义
typedef enum {
    LIGHT_LEVEL_DARK = 0,    // 黑暗
    LIGHT_LEVEL_DIM,         // 昏暗
    LIGHT_LEVEL_NORMAL,      // 正常
    LIGHT_LEVEL_BRIGHT       // 明亮
} LightLevel;

// 光敏传感器函数
uint16_t LightSensor_GetValue(void);   // 获取ADC原始值（0-4095）
uint8_t LightSensor_GetPercent(void);  // 获取光照百分比（0-100）
LightLevel LightSensor_GetLevel(void); // 获取光照等级

#endif
