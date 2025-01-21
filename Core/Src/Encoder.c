#include "encoder.h"
// 定义编码器结构体变量
static EncoderTypeDef encoder;

/**
 * @brief  初始化编码器
 * @param  None
 * @retval None
 */
void Encoder_Init(void)
{
  // 初始化编码器变量
  encoder.count = 0;
  encoder.lastCount = 0;
  encoder.buttonState = 0;
  // 启动定时器
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

/**
 * @brief  获取编码器状态
 * @param  None
 * @retval EncoderState: 编码器状态
 */
EncoderState Encoder_GetState(void)
{
  // diff为编码器计数差值
  int16_t diff = (int16_t)(Encoder_GetCount() - encoder.lastCount);
  // 如果按钮状态为1，则为按下按钮
  if (encoder.buttonState)
    return ENCODER_PUSH;
  // 如果计数差值大于0，则为顺时针旋转
  else if (diff > 0)
    return ENCODER_CW;
  // 如果计数差值小于0，则为逆时针旋转
  else if (diff < 0)
    return ENCODER_CCW;
  // 否则为空闲状态
  else
    return ENCODER_IDLE;
}

/**
 * @brief  获取编码器计数值
 * @param  None
 * @retval int16_t: 计数值
 */
int16_t Encoder_GetCount(void)
{
  // 将当前计数值赋值给lastCount
  encoder.lastCount = encoder.count;
  // 将当前计数值赋值给count &htim3是TIM3 的句柄（TIM_HandleTypeDef 结构体）的地址
  encoder.count = (int16_t)__HAL_TIM_GET_COUNTER(&htim3);

  // 返回当前计数值
  return encoder.count;
}

/**
 * @brief  获取按钮状态
 * @param  None
 * @retval uint8_t: 按钮状态，1为按下，0为释放
 */
uint8_t Encoder_GetButtonState(void)
{
  return encoder.buttonState;
}

/**
 * @brief  设置编码器计数值
 * @param  count: 计数值
 * @retval None
 */
void Encoder_SetCount(int16_t count)
{
  encoder.count = count;
  encoder.lastCount = encoder.count;
  __HAL_TIM_SET_COUNTER(&htim3, (uint16_t)count);
}

/**
 * @brief  清除编码器计数值
 * @param  None
 * @retval None
 */
void Encoder_ClearCount(void)
{
  Encoder_SetCount(0);
}
