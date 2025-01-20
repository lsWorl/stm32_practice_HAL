#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H
#include "adc.h"
#include "gpio.h"
#include "stm32f1xx_hal.h"  // ���� HAL ��ͷ�ļ�

// ����ǿ�ȵȼ�����
typedef enum {
    LIGHT_LEVEL_DARK = 0,    // �ڰ�
    LIGHT_LEVEL_DIM,         // �谵
    LIGHT_LEVEL_NORMAL,      // ����
    LIGHT_LEVEL_BRIGHT       // ����
} LightLevel;

// ��������������
void LightSensor_Init(void);           // ��ʼ������������
uint16_t LightSensor_GetValue(void);   // ��ȡADCԭʼֵ��0-4095��
uint8_t LightSensor_GetPercent(void);  // ��ȡ���հٷֱȣ�0-100��
LightLevel LightSensor_GetLevel(void); // ��ȡ���յȼ�

#endif
