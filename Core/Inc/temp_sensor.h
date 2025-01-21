#ifndef __TEMP_SENSOR_H
#define __TEMP_SENSOR_H
#include "adc.h"
#include "gpio.h"
#include "stm32f1xx_hal.h"  // ���� HAL ��ͷ�ļ�
// �¶ȵȼ�����
typedef enum {
    TEMP_LOW = 0,     // �¶ȹ���
    TEMP_NORMAL,      // �¶�����
    TEMP_HIGH,        // �¶�ƫ��
    TEMP_ALERT        // �¶Ⱦ���
} TempLevel;

// �¶ȴ���������
uint16_t TempSensor_GetADC(void);     // ��ȡADCԭʼֵ
float TempSensor_GetTemp(void);       // ��ȡʵ���¶�ֵ�����϶ȣ�
TempLevel TempSensor_GetLevel(void);  // ��ȡ�¶ȵȼ�
#endif
