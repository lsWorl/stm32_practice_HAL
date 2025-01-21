#include "light_sensor.h"

// ���յȼ���ֵ���壨ADCֵ��
#define LIGHT_THRESHOLD_DARK 3000   // �ڰ���ֵ
#define LIGHT_THRESHOLD_DIM 1500    // �谵��ֵ
#define LIGHT_THRESHOLD_NORMAL 1000 // ������ֵ


/**
 * @brief  ��ȡADCת��ֵ
 * @param  None
 * @retval uint16_t: ADCת�����(0-4095)
 */
uint16_t LightSensor_GetValue(void)
{
  // ����ת�����
  return light_sensor_value;
}

/**
 * @brief  ��ȡ����ǿ�Ȱٷֱ�
 * @param  None
 * @retval uint8_t: ����ǿ�Ȱٷֱ�(0-100)
 */
uint8_t LightSensor_GetPercent(void)
{
  uint32_t value = LightSensor_GetValue();
  // ��ADCֵ��0-4095��ת��Ϊ�ٷֱȣ�0-100��
  return (uint8_t)(100 - ((value * 100) / 4095));
}

/**
 * @brief  ��ȡ���յȼ�
 * @param  None
 * @retval LightLevel: ���յȼ�
 */
LightLevel LightSensor_GetLevel(void)
{
  uint16_t value = LightSensor_GetValue();

  if (value > LIGHT_THRESHOLD_NORMAL && value < LIGHT_THRESHOLD_DIM) // ģ������1000-1500֮��Ϊ��������
    return LIGHT_LEVEL_NORMAL;
  else if (value > LIGHT_THRESHOLD_DIM && value < LIGHT_THRESHOLD_DARK) // ģ������1500-3000֮��Ϊ�谵����
    return LIGHT_LEVEL_DIM;
  else if (value > LIGHT_THRESHOLD_DARK) // ģ������3000����Ϊ�ڰ�����
    return LIGHT_LEVEL_DARK;
  else
    return LIGHT_LEVEL_BRIGHT;
}
