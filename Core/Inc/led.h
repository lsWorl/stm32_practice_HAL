#ifndef __LED_H
#define __LED_H

#include "gpio.h"

// LED���ƺ���
void LED_On(uint16_t LED_PIN);
void LED_Off(uint16_t LED_PIN);
void LED_Toggle(uint16_t LED_PIN);

// LED״̬����
void LED_AllOn(void);
void LED_AllOff(void);
void LED_SystemRunning(void);    // LED1ָʾϵͳ����
void LED_DataCollecting(void);   // LED2ָʾ���ݲɼ�
void LED_SettingMode(void);      // LED3ָʾ����ģʽ
void LED_AlarmStatus(void);      // LED4ָʾ����״̬

#endif
