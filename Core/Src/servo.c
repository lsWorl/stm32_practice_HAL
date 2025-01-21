#include "servo.h"
// ��ǰ����Ƕ�
static uint8_t currentAngle = 90;

/**
  * @brief  ��ʼ�����
  * @param  None
  * @retval None
  */
void Servo_Init(void)
{
    // ���� TIM1 �� PWM ���
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    
    // ��λ���м�λ��
    Servo_Reset();
}

/**
  * @brief  ���ö���Ƕ�
  * @param  angle: Ŀ��Ƕȣ�0-180�ȣ�
  * @retval None
  */
void Servo_SetAngle(uint8_t angle)
{
    uint16_t pulse;
    
    // ���ƽǶȷ�Χ
    if(angle > SERVO_MAX_ANGLE)
        angle = SERVO_MAX_ANGLE;
    
    // �Ƕ�ת��Ϊ������
    // pulse = 500 + (angle/180) * 2000
    pulse = SERVO_MIN_PULSE + ((uint32_t)angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE)) / SERVO_MAX_ANGLE;
    
    // ����PWMռ�ձ�
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse);
    
    // ���µ�ǰ�Ƕ�
    currentAngle = angle;
}

/**
  * @brief  ���ö��������
  * @param  pulse: �����ȣ�500-2500us��
  * @retval None
  */
void Servo_SetPulse(uint16_t pulse)
{
    // ���������ȷ�Χ
    if(pulse < SERVO_MIN_PULSE)
        pulse = SERVO_MIN_PULSE;
    else if(pulse > SERVO_MAX_PULSE)
        pulse = SERVO_MAX_PULSE;
    
    // ����PWMռ�ձ�
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse);
    
    // ���µ�ǰ�Ƕ�
    currentAngle = ((pulse - SERVO_MIN_PULSE) * SERVO_MAX_ANGLE) / (SERVO_MAX_PULSE - SERVO_MIN_PULSE);
}

/**
  * @brief  ��ȡ��ǰ����Ƕ�
  * @param  None
  * @retval uint8_t: ��ǰ�Ƕȣ�0-180�ȣ�
  */
uint8_t Servo_GetAngle(void)
{
    return currentAngle;
}

/**
  * @brief  ��λ������м�λ��
  * @param  None
  * @retval None
  */
void Servo_Reset(void)
{
    Servo_SetAngle(90);  // ��λ��90��λ��
}
