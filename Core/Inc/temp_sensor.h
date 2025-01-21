#ifndef __TEMP_SENSOR_H
#define __TEMP_SENSOR_H
#include "adc.h"
#include "gpio.h"
#include "stm32f1xx_hal.h"  // 包含 HAL 库头文件
// 温度等级定义
typedef enum {
    TEMP_LOW = 0,     // 温度过低
    TEMP_NORMAL,      // 温度正常
    TEMP_HIGH,        // 温度偏高
    TEMP_ALERT        // 温度警告
} TempLevel;

// 温度传感器函数
uint16_t TempSensor_GetADC(void);     // 获取ADC原始值
float TempSensor_GetTemp(void);       // 获取实际温度值（摄氏度）
TempLevel TempSensor_GetLevel(void);  // 获取温度等级
#endif
