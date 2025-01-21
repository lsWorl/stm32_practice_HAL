#ifndef __SYSTEM_H
#define __SYSTEM_H
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

#include "led.h"
#include "OLED.h"
#include "Beeper.h"
#include "Button.h"
#include "Encoder.h"
#include "light_sensor.h"
#include "temp_sensor.h"
#include "mpu6050.h"
#include "servo.h"
// ϵͳ����ģʽ����
typedef enum {
    SYS_MODE_MONITOR = 0,    // ���ģʽ����ʾ���д���������
    SYS_MODE_SETTING,        // ����ģʽ����������
    SYS_MODE_DEBUG           // ����ģʽ�����Ե���ģ��
} SystemMode;

// ϵͳ״̬����
typedef struct {
    SystemMode mode;         // ��ǰ����ģʽ
    uint8_t isAlarming;     // �Ƿ��ڱ���״̬
    uint8_t isInitialized;  // �Ƿ��ѳ�ʼ��
    
    // ����������
    float temperature;      // �¶�ֵ
    uint8_t lightLevel;     // ���յȼ�
    MPU6050_Attitude attitude;  // ��̬����
    
    // ���ò���
    float tempThreshold;    // �¶ȱ�����ֵ
    uint8_t servoAngle;     // ����Ƕ�
} SystemState;

// ϵͳ����
void System_Init(void);                    // ϵͳ��ʼ��
void System_Process(void);                 // ϵͳ��������
void System_SetMode(SystemMode mode);      // ����ϵͳģʽ
void System_UpdateDisplay(void);           // ������ʾ
void System_CheckAlarm(void);             // ��鱨������
void System_HandleInput(void);             // �����û�����
void Servo_Running(void);                   // ������ֵ����ת�����
// ��ȡϵͳ״̬
SystemState* System_GetState(void);

#endif
