#ifndef __SERVO_H
#define __SERVO_H
#include "gpio.h"
#include "stm32f1xx_hal.h" // ���� HAL ��ͷ�ļ�
#include "tim.h"
// �����������
#define SERVO_PERIOD 20000   // PWM���ڣ���λ��us��
#define SERVO_MIN_PULSE 500  // ��С�����ȣ�0��λ�ã�
#define SERVO_MAX_PULSE 2500 // ��������ȣ�180��λ�ã�
#define SERVO_MID_PULSE 1500 // �м������ȣ�90��λ�ã�

// ����Ƕȷ�Χ
#define SERVO_MIN_ANGLE 0   // ��С�Ƕ�
#define SERVO_MAX_ANGLE 180 // ���Ƕ�

// �������
void Servo_Init(void);               // ��ʼ�����
void Servo_SetAngle(uint8_t angle);  // ���ö���Ƕȣ�0-180�ȣ�
void Servo_SetPulse(uint16_t pulse); // ���ö�������ȣ�500-2500us��
uint8_t Servo_GetAngle(void);        // ��ȡ��ǰ����Ƕ�
void Servo_Reset(void);              // ��λ������м�λ�ã�90�ȣ�
#endif
