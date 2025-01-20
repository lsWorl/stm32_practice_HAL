#include "Beeper.h"

/**
 * @brief  �򿪷�����
 * @param  None
 * @retval None
 */
void Beeper_On(void)
{
  HAL_GPIO_WritePin(GPIOA, Beeper_Pin, GPIO_PIN_RESET);
}

/**
 * @brief  �رշ�����
 * @param  None
 * @retval None
 */
void Beeper_Off(void)
{
  HAL_GPIO_WritePin(GPIOA, Beeper_Pin, GPIO_PIN_SET);
}

/**
 * @brief  �л�������״̬
 * @param  None
 * @retval None
 */
void Beeper_Toggle(void)
{
  HAL_GPIO_TogglePin(GPIOA, Beeper_Pin);
}

/**
 * @brief  ����������ָ��ʱ��
 * @param  ms: ����ʱ��(����)
 * @retval None
 */
void Beeper_Beep(uint16_t ms)
{
  Beeper_On();
  HAL_Delay(ms);
  Beeper_Off();
}
