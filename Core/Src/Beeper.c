#include "Beeper.h"

/**
 * @brief  打开蜂鸣器
 * @param  None
 * @retval None
 */
void Beeper_On(void)
{
  HAL_GPIO_WritePin(GPIOA, Beeper_Pin, GPIO_PIN_RESET);
}

/**
 * @brief  关闭蜂鸣器
 * @param  None
 * @retval None
 */
void Beeper_Off(void)
{
  HAL_GPIO_WritePin(GPIOA, Beeper_Pin, GPIO_PIN_SET);
}

/**
 * @brief  切换蜂鸣器状态
 * @param  None
 * @retval None
 */
void Beeper_Toggle(void)
{
  HAL_GPIO_TogglePin(GPIOA, Beeper_Pin);
}

/**
 * @brief  蜂鸣器鸣叫指定时长
 * @param  ms: 鸣叫时长(毫秒)
 * @retval None
 */
void Beeper_Beep(uint16_t ms)
{
  Beeper_On();
  HAL_Delay(ms);
  Beeper_Off();
}
