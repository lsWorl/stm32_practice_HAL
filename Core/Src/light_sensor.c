#include "light_sensor.h"

// 光照等级阈值定义（ADC值）
#define LIGHT_THRESHOLD_DARK 3000   // 黑暗阈值
#define LIGHT_THRESHOLD_DIM 1500    // 昏暗阈值
#define LIGHT_THRESHOLD_NORMAL 1000 // 正常阈值


/**
 * @brief  获取ADC转换值
 * @param  None
 * @retval uint16_t: ADC转换结果(0-4095)
 */
uint16_t LightSensor_GetValue(void)
{
  // 返回转换结果
  return light_sensor_value;
}

/**
 * @brief  获取光照强度百分比
 * @param  None
 * @retval uint8_t: 光照强度百分比(0-100)
 */
uint8_t LightSensor_GetPercent(void)
{
  uint32_t value = LightSensor_GetValue();
  // 将ADC值（0-4095）转换为百分比（0-100）
  return (uint8_t)(100 - ((value * 100) / 4095));
}

/**
 * @brief  获取光照等级
 * @param  None
 * @retval LightLevel: 光照等级
 */
LightLevel LightSensor_GetLevel(void)
{
  uint16_t value = LightSensor_GetValue();

  if (value > LIGHT_THRESHOLD_NORMAL && value < LIGHT_THRESHOLD_DIM) // 模拟量在1000-1500之间为正常光照
    return LIGHT_LEVEL_NORMAL;
  else if (value > LIGHT_THRESHOLD_DIM && value < LIGHT_THRESHOLD_DARK) // 模拟量在1500-3000之间为昏暗光照
    return LIGHT_LEVEL_DIM;
  else if (value > LIGHT_THRESHOLD_DARK) // 模拟量在3000以上为黑暗光照
    return LIGHT_LEVEL_DARK;
  else
    return LIGHT_LEVEL_BRIGHT;
}
