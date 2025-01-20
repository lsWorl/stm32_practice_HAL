#include "led.h"

/**
  * @brief  ����LED
  * @param  None
  * @retval None
  */
void LED_On(uint16_t LED_PIN)
{
    HAL_GPIO_WritePin(GPIOA, LED_PIN, GPIO_PIN_RESET);
}

/**
  * @brief  Ϩ��LED
  * @param  None
  * @retval None
  */
void LED_Off(uint16_t LED_PIN)
{
    HAL_GPIO_WritePin(GPIOA, LED_PIN, GPIO_PIN_SET);
}

/**
  * @brief  �л�LED״̬
  * @param  None
  * @retval None
  */
void LED_Toggle(uint16_t LED_PIN)
{
    HAL_GPIO_TogglePin(GPIOA, LED_PIN);
}

/**
  * @brief  ��������LED
  * @param  None
  * @retval None
  */
void LED_AllOn(void)
{
    HAL_GPIO_WritePin(GPIOA, LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin, GPIO_PIN_RESET);
}

/**
  * @brief  Ϩ������LED
  * @param  None
  * @retval None
  */
void LED_AllOff(void)
{
    HAL_GPIO_WritePin(GPIOA, LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin, GPIO_PIN_SET);
}

/**
  * @brief  ϵͳ����ָʾ��LED1��
  * @param  None
  * @retval None
  */
void LED_SystemRunning(void)
{
    LED_Toggle(LED1_Pin);
}

/**
  * @brief  ���ݲɼ�ָʾ��LED2��
  * @param  None
  * @retval None
  */
void LED_DataCollecting(void)
{
    LED_On(LED2_Pin);
}

/**
  * @brief  ����ģʽָʾ��LED3��
  * @param  None
  * @retval None
  */
void LED_SettingMode(void)
{
    LED_On(LED3_Pin);
}

/**
  * @brief  ����״ָ̬ʾ��LED4��
  * @param  None
  * @retval None
  */
void LED_AlarmStatus(void)
{
    LED_Toggle(LED4_Pin);
}
