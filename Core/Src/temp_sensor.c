#include "temp_sensor.h"
#include <math.h>

// �¶���ֵ���壨���϶ȣ�
#define TEMP_THRESHOLD_LOW    10.0f  // ������ֵ
#define TEMP_THRESHOLD_HIGH   20.0f  // ������ֵ
#define TEMP_THRESHOLD_ALERT  30.0f  // ������ֵ

// NTC�����������
#define TEMP_NOMINAL         25.0f   // ����¶ȣ����϶ȣ�
#define THERMISTOR_NOMINAL   10000.0f // ��Ƶ��裨ŷķ��
#define BCOEFFICIENT        3950.0f  // Betaϵ��
#define SERIES_RESISTOR     10000.0f // ��ѹ���裨ŷķ��


/**
  * @brief  ��ȡADCת��ֵ
  * @param  None
  * @retval uint16_t: ADCת�����(0-4095)
  */
uint16_t TempSensor_GetADC(void)
{
    // ����ת�����
    return temp_sensor_value;
}

/**
  * @brief  ��ȡʵ���¶�ֵ
  * @param  None
  * @retval float: �¶�ֵ�����϶ȣ�
  */
float TempSensor_GetTemp(void)
{
    float adc_value, resistance, steinhart;
    
    // ��ȡADCֵ���������ֵ
    adc_value = (float)TempSensor_GetADC();
    resistance = SERIES_RESISTOR / ((4095.0f / adc_value) - 1.0f);
    
    // ʹ��Steinhart-Hart���̼����¶�
    steinhart = resistance / THERMISTOR_NOMINAL;     // (R/Ro)
    steinhart = log(steinhart);                     // ln(R/Ro)
    steinhart /= BCOEFFICIENT;                      // 1/B * ln(R/Ro)
    steinhart += 1.0f / (TEMP_NOMINAL + 273.15f);   // + (1/To)
    steinhart = 1.0f / steinhart;                   // ����
    steinhart -= 273.15f;                           // ת��Ϊ���϶�
    
    return steinhart;
}

/**
  * @brief  ��ȡ�¶ȵȼ�
  * @param  None
  * @retval TempLevel: �¶ȵȼ�
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
