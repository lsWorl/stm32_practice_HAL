#include "Button.h"

// ������������
#define BUTTON_SCAN_INTERVAL 20 // ɨ������ms��
#define LONG_PRESS_TIME 2000    // ����ʱ�䣨ms��
#define DEBOUNCE_TIME 20        // ����ʱ�䣨ms��

// ����״̬��¼
static struct
{
  ButtonState state;  // �����߼�״̬
  uint32_t pressTime; // ����ʱ��
  uint8_t isPressed;  // �����Ƿ��ڰ���״̬
} keyInfo[KEY_COUNT] = {BTN_IDLE, 0, 0};

// �������Ŷ���
static const uint16_t KEY_PINS[KEY_COUNT] = {
    BTN1_Pin, // KEY_MODE  (BTN1)
    BTN2_Pin, // KEY_CONFIRM (BTN2)
    BTN3_Pin, // KEY_ALARM (BTN3)
    BTN4_Pin  // KEY_RESET (BTN4)
};

static GPIO_TypeDef *const KEY_PORTS[KEY_COUNT] = {
    GPIOA, // KEY_MODE  (PA5)
    GPIOB, // KEY_CONFIRM (PB0)
    GPIOB, // KEY_ALARM (PB1)
    GPIOB  // KEY_RESET (PB12)
};

/**
 * @brief  ����ɨ�账�� ��Ҫ���ڰ���״̬�ĸ���
 * @param  None
 * @retval None
 */
void Button_Scan(void)
{
  static uint32_t lastScanTime = 0;
  uint32_t currentTime;
  uint8_t i;
  // ��ȡ��ǰʱ��
  currentTime = HAL_GetTick();

  // ��ɨ�������д��� С��ɨ�����򲻴���
  if (currentTime - lastScanTime < BUTTON_SCAN_INTERVAL)
    return;

  // ����ɨ��ʱ��
  lastScanTime = currentTime;

  for (i = 0; i < KEY_COUNT; i++)
  {
    // ��ȡ����״̬
    uint8_t pinState = HAL_GPIO_ReadPin(KEY_PORTS[i], KEY_PINS[i]);

    if (pinState == 0) // ��������
    {
      if (!keyInfo[i].isPressed) // isPressedΪ0��ʾ����δ����
      {
        keyInfo[i].isPressed = 1;
        keyInfo[i].pressTime = currentTime;
        keyInfo[i].state = BTN_DEBOUNCE;
      }
      else if (keyInfo[i].state == BTN_DEBOUNCE) // ������������״̬
      {
        if (currentTime - keyInfo[i].pressTime >= LONG_PRESS_TIME) // ��������ʱ����ڳ���ʱ��
        {
          keyInfo[i].state = BTN_LONG_PRESS; // ����״̬����Ϊ����״̬
        }
      }
    }
    else // �����ͷ�
    {
      if (keyInfo[i].isPressed)
      {
        if (currentTime - keyInfo[i].pressTime >= DEBOUNCE_TIME)
        {
          if (keyInfo[i].state != BTN_LONG_PRESS)
          {
            keyInfo[i].state = BTN_SHORT_PRESS;
          }
        }
        keyInfo[i].isPressed = 0;
      }
    }
  }
}

/**
 * @brief  ��ȡ����״̬
 * @param  key: �������
 * @retval ButtonState: ����״̬
 */
ButtonState Button_GetState(KeyID key)
{
  if (key >= KEY_COUNT)
    return BTN_IDLE;
  return keyInfo[key].state;
}

/**
 * @brief  �������״̬
 * @param  key: �������
 * @retval None
 */
void Button_ClearState(KeyID key)
{
  if (key < KEY_COUNT)
  {
    keyInfo[key].state = BTN_IDLE;
    keyInfo[key].isPressed = 0;
  }
}

// ��д�����ص�����
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  // ��һ�����������ж�
  if (GPIO_Pin == BTN1_Pin)
  {
    keyInfo[KEY_MODE].pressTime = HAL_GetTick();
    keyInfo[KEY_MODE].state = BTN_DEBOUNCE;
    keyInfo[KEY_MODE].isPressed = 1;
  }
  // �ڶ������������ж�
  if (GPIO_Pin == BTN2_Pin)
  {
    keyInfo[KEY_CONFIRM].pressTime = HAL_GetTick();
    keyInfo[KEY_CONFIRM].state = BTN_DEBOUNCE;
    keyInfo[KEY_CONFIRM].isPressed = 1;
  }
  // ���������������ж�
  if (GPIO_Pin == BTN3_Pin)
  {
    keyInfo[KEY_ALARM].pressTime = HAL_GetTick();
    keyInfo[KEY_ALARM].state = BTN_DEBOUNCE;
    keyInfo[KEY_ALARM].isPressed = 1;
  }
  // ���ĸ����������ж�
  if (GPIO_Pin == BTN4_Pin)
  {
    keyInfo[KEY_RESET].pressTime = HAL_GetTick();
    keyInfo[KEY_RESET].state = BTN_DEBOUNCE;
    keyInfo[KEY_RESET].isPressed = 1;
  }
}
