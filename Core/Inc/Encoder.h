#ifndef __ENCODER_H
#define __ENCODER_H

#include "gpio.h"
#include "stm32f1xx_hal.h"  // ���� HAL ��ͷ�ļ�
#include "tim.h"
// ������״̬����
typedef enum {
    ENCODER_IDLE = 0,    // ����״̬
    ENCODER_CW,          // ˳ʱ����ת
    ENCODER_CCW,         // ��ʱ����ת
    ENCODER_PUSH         // ���°�ť
} EncoderState;

// �����������ṹ��
typedef struct {
    int16_t count;       // ����������ֵ
    int16_t lastCount;   // �ϴεļ���ֵ
    uint8_t buttonState; // ��ť״̬
} EncoderTypeDef;

// ����������
void Encoder_Init(void);                     // ��ʼ��������
EncoderState Encoder_GetState(void);         // ��ȡ������״̬
int16_t Encoder_GetCount(void);             // ��ȡ����������ֵ
uint8_t Encoder_GetButtonState(void);        // ��ȡ��ť״̬
void Encoder_SetCount(int16_t count);       // ���ñ���������ֵ
void Encoder_ClearCount(void);              // �������������ֵ

#endif
