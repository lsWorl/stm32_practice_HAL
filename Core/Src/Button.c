#include "Button.h"

// 按键参数定义
#define BUTTON_SCAN_INTERVAL 20 // 扫描间隔（ms）
#define LONG_PRESS_TIME 2000    // 长按时间（ms）
#define DEBOUNCE_TIME 20        // 消抖时间（ms）

// 按键状态记录
static struct
{
  ButtonState state;  // 按键逻辑状态
  uint32_t pressTime; // 按下时刻
  uint8_t isPressed;  // 按键是否处于按下状态
} keyInfo[KEY_COUNT] = {BTN_IDLE, 0, 0};

// 按键引脚定义
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
 * @brief  按键扫描处理 主要用于按键状态的更新
 * @param  None
 * @retval None
 */
void Button_Scan(void)
{
  static uint32_t lastScanTime = 0;
  uint32_t currentTime;
  uint8_t i;
  // 获取当前时间
  currentTime = HAL_GetTick();

  // 按扫描间隔进行处理 小于扫描间隔则不处理
  if (currentTime - lastScanTime < BUTTON_SCAN_INTERVAL)
    return;

  // 更新扫描时间
  lastScanTime = currentTime;

  for (i = 0; i < KEY_COUNT; i++)
  {
    // 读取按键状态
    uint8_t pinState = HAL_GPIO_ReadPin(KEY_PORTS[i], KEY_PINS[i]);

    if (pinState == 0) // 按键按下
    {
      if (!keyInfo[i].isPressed) // isPressed为0表示按键未按下
      {
        keyInfo[i].isPressed = 1;
        keyInfo[i].pressTime = currentTime;
        keyInfo[i].state = BTN_DEBOUNCE;
      }
      else if (keyInfo[i].state == BTN_DEBOUNCE) // 按键处于消抖状态
      {
        if (currentTime - keyInfo[i].pressTime >= LONG_PRESS_TIME) // 按键按下时间大于长按时间
        {
          keyInfo[i].state = BTN_LONG_PRESS; // 按键状态设置为长按状态
        }
      }
    }
    else // 按键释放
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
 * @brief  获取按键状态
 * @param  key: 按键编号
 * @retval ButtonState: 按键状态
 */
ButtonState Button_GetState(KeyID key)
{
  if (key >= KEY_COUNT)
    return BTN_IDLE;
  return keyInfo[key].state;
}

/**
 * @brief  清除按键状态
 * @param  key: 按键编号
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

// 重写按键回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  // 第一个按键触发中断
  if (GPIO_Pin == BTN1_Pin)
  {
    keyInfo[KEY_MODE].pressTime = HAL_GetTick();
    keyInfo[KEY_MODE].state = BTN_DEBOUNCE;
    keyInfo[KEY_MODE].isPressed = 1;
  }
  // 第二个按键触发中断
  if (GPIO_Pin == BTN2_Pin)
  {
    keyInfo[KEY_CONFIRM].pressTime = HAL_GetTick();
    keyInfo[KEY_CONFIRM].state = BTN_DEBOUNCE;
    keyInfo[KEY_CONFIRM].isPressed = 1;
  }
  // 第三个按键触发中断
  if (GPIO_Pin == BTN3_Pin)
  {
    keyInfo[KEY_ALARM].pressTime = HAL_GetTick();
    keyInfo[KEY_ALARM].state = BTN_DEBOUNCE;
    keyInfo[KEY_ALARM].isPressed = 1;
  }
  // 第四个按键触发中断
  if (GPIO_Pin == BTN4_Pin)
  {
    keyInfo[KEY_RESET].pressTime = HAL_GetTick();
    keyInfo[KEY_RESET].state = BTN_DEBOUNCE;
    keyInfo[KEY_RESET].isPressed = 1;
  }
}
