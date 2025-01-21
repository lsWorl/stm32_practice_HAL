#include "servo.h"
// 当前舵机角度
static uint8_t currentAngle = 90;

/**
  * @brief  初始化舵机
  * @param  None
  * @retval None
  */
void Servo_Init(void)
{
    // 启动 TIM1 的 PWM 输出
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    
    // 复位到中间位置
    Servo_Reset();
}

/**
  * @brief  设置舵机角度
  * @param  angle: 目标角度（0-180度）
  * @retval None
  */
void Servo_SetAngle(uint8_t angle)
{
    uint16_t pulse;
    
    // 限制角度范围
    if(angle > SERVO_MAX_ANGLE)
        angle = SERVO_MAX_ANGLE;
    
    // 角度转换为脉冲宽度
    // pulse = 500 + (angle/180) * 2000
    pulse = SERVO_MIN_PULSE + ((uint32_t)angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE)) / SERVO_MAX_ANGLE;
    
    // 设置PWM占空比
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse);
    
    // 更新当前角度
    currentAngle = angle;
}

/**
  * @brief  设置舵机脉冲宽度
  * @param  pulse: 脉冲宽度（500-2500us）
  * @retval None
  */
void Servo_SetPulse(uint16_t pulse)
{
    // 限制脉冲宽度范围
    if(pulse < SERVO_MIN_PULSE)
        pulse = SERVO_MIN_PULSE;
    else if(pulse > SERVO_MAX_PULSE)
        pulse = SERVO_MAX_PULSE;
    
    // 设置PWM占空比
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse);
    
    // 更新当前角度
    currentAngle = ((pulse - SERVO_MIN_PULSE) * SERVO_MAX_ANGLE) / (SERVO_MAX_PULSE - SERVO_MIN_PULSE);
}

/**
  * @brief  获取当前舵机角度
  * @param  None
  * @retval uint8_t: 当前角度（0-180度）
  */
uint8_t Servo_GetAngle(void)
{
    return currentAngle;
}

/**
  * @brief  复位舵机到中间位置
  * @param  None
  * @retval None
  */
void Servo_Reset(void)
{
    Servo_SetAngle(90);  // 复位到90度位置
}
