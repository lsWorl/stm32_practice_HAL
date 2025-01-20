#include "led.h"

/**
  * @brief  点亮LED
  * @param  None
  * @retval None
  */
void LED_On(uint16_t LED_PIN)
{
    HAL_GPIO_WritePin(GPIOA, LED_PIN, GPIO_PIN_RESET);
}

/**
  * @brief  熄灭LED
  * @param  None
  * @retval None
  */
void LED_Off(uint16_t LED_PIN)
{
    HAL_GPIO_WritePin(GPIOA, LED_PIN, GPIO_PIN_SET);
}

/**
  * @brief  切换LED状态
  * @param  None
  * @retval None
  */
void LED_Toggle(uint16_t LED_PIN)
{
    HAL_GPIO_TogglePin(GPIOA, LED_PIN);
}

/**
  * @brief  点亮所有LED
  * @param  None
  * @retval None
  */
void LED_AllOn(void)
{
    HAL_GPIO_WritePin(GPIOA, LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin, GPIO_PIN_RESET);
}

/**
  * @brief  熄灭所有LED
  * @param  None
  * @retval None
  */
void LED_AllOff(void)
{
    HAL_GPIO_WritePin(GPIOA, LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin, GPIO_PIN_SET);
}

/**
  * @brief  系统运行指示（LED1）
  * @param  None
  * @retval None
  */
void LED_SystemRunning(void)
{
    LED_Toggle(LED1_Pin);
}

/**
  * @brief  数据采集指示（LED2）
  * @param  None
  * @retval None
  */
void LED_DataCollecting(void)
{
    LED_On(LED2_Pin);
}

/**
  * @brief  设置模式指示（LED3）
  * @param  None
  * @retval None
  */
void LED_SettingMode(void)
{
    LED_On(LED3_Pin);
}

/**
  * @brief  报警状态指示（LED4）
  * @param  None
  * @retval None
  */
void LED_AlarmStatus(void)
{
    LED_Toggle(LED4_Pin);
}
