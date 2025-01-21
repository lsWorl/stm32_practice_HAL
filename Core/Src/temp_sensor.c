#include "temp_sensor.h"
#include <math.h>

// 温度阈值定义（摄氏度）
#define TEMP_THRESHOLD_LOW    10.0f  // 低温阈值
#define TEMP_THRESHOLD_HIGH   20.0f  // 高温阈值
#define TEMP_THRESHOLD_ALERT  30.0f  // 警告阈值

// NTC热敏电阻参数
#define TEMP_NOMINAL         25.0f   // 标称温度（摄氏度）
#define THERMISTOR_NOMINAL   10000.0f // 标称电阻（欧姆）
#define BCOEFFICIENT        3950.0f  // Beta系数
#define SERIES_RESISTOR     10000.0f // 分压电阻（欧姆）


/**
  * @brief  获取ADC转换值
  * @param  None
  * @retval uint16_t: ADC转换结果(0-4095)
  */
uint16_t TempSensor_GetADC(void)
{
    // 返回转换结果
    return temp_sensor_value;
}

/**
  * @brief  获取实际温度值
  * @param  None
  * @retval float: 温度值（摄氏度）
  */
float TempSensor_GetTemp(void)
{
    float adc_value, resistance, steinhart;
    
    // 获取ADC值并计算电阻值
    adc_value = (float)TempSensor_GetADC();
    resistance = SERIES_RESISTOR / ((4095.0f / adc_value) - 1.0f);
    
    // 使用Steinhart-Hart方程计算温度
    steinhart = resistance / THERMISTOR_NOMINAL;     // (R/Ro)
    steinhart = log(steinhart);                     // ln(R/Ro)
    steinhart /= BCOEFFICIENT;                      // 1/B * ln(R/Ro)
    steinhart += 1.0f / (TEMP_NOMINAL + 273.15f);   // + (1/To)
    steinhart = 1.0f / steinhart;                   // 倒数
    steinhart -= 273.15f;                           // 转换为摄氏度
    
    return steinhart;
}

/**
  * @brief  获取温度等级
  * @param  None
  * @retval TempLevel: 温度等级
  */
TempLevel TempSensor_GetLevel(void)
{
    float temp = TempSensor_GetTemp();
    
    if(temp < TEMP_THRESHOLD_LOW)
        return TEMP_LOW;
    else if(temp < TEMP_THRESHOLD_HIGH)
        return TEMP_NORMAL;
    else if(temp < TEMP_THRESHOLD_ALERT)
        return TEMP_HIGH;
    else
        return TEMP_ALERT;
}
