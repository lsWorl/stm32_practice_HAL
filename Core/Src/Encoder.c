#include "encoder.h"
// ����������ṹ�����
static EncoderTypeDef encoder;

/**
 * @brief  ��ʼ��������
 * @param  None
 * @retval None
 */
void Encoder_Init(void)
{
  // ��ʼ������������
  encoder.count = 0;
  encoder.lastCount = 0;
  encoder.buttonState = 0;
  // ������ʱ��
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

/**
 * @brief  ��ȡ������״̬
 * @param  None
 * @retval EncoderState: ������״̬
 */
EncoderState Encoder_GetState(void)
{
  // diffΪ������������ֵ
  int16_t diff = (int16_t)(Encoder_GetCount() - encoder.lastCount);
  // �����ť״̬Ϊ1����Ϊ���°�ť
  if (encoder.buttonState)
    return ENCODER_PUSH;
  // ���������ֵ����0����Ϊ˳ʱ����ת
  else if (diff > 0)
    return ENCODER_CW;
  // ���������ֵС��0����Ϊ��ʱ����ת
  else if (diff < 0)
    return ENCODER_CCW;
  // ����Ϊ����״̬
  else
    return ENCODER_IDLE;
}

/**
 * @brief  ��ȡ����������ֵ
 * @param  None
 * @retval int16_t: ����ֵ
 */
int16_t Encoder_GetCount(void)
{
  // ����ǰ����ֵ��ֵ��lastCount
  encoder.lastCount = encoder.count;
  // ����ǰ����ֵ��ֵ��count &htim3��TIM3 �ľ����TIM_HandleTypeDef �ṹ�壩�ĵ�ַ
  encoder.count = (int16_t)__HAL_TIM_GET_COUNTER(&htim3);

  // ���ص�ǰ����ֵ
  return encoder.count;
}

/**
 * @brief  ��ȡ��ť״̬
 * @param  None
 * @retval uint8_t: ��ť״̬��1Ϊ���£�0Ϊ�ͷ�
 */
uint8_t Encoder_GetButtonState(void)
{
  return encoder.buttonState;
}

/**
 * @brief  ���ñ���������ֵ
 * @param  count: ����ֵ
 * @retval None
 */
void Encoder_SetCount(int16_t count)
{
  encoder.count = count;
  encoder.lastCount = encoder.count;
  __HAL_TIM_SET_COUNTER(&htim3, (uint16_t)count);
}

/**
 * @brief  �������������ֵ
 * @param  None
 * @retval None
 */
void Encoder_ClearCount(void)
{
  Encoder_SetCount(0);
}
