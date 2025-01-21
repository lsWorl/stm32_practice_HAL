#include "system.h"
// ϵͳ״̬����
static SystemState systemState = {
    SYS_MODE_MONITOR,   // ���ģʽ
    0,                  // �Ƿ��ڱ���״̬
    0,                  // �Ƿ��ѳ�ʼ��
    0.0f,               // �¶�ֵ
    0,                  // ���յȼ�
    {0.0f, 0.0f, 0.0f}, // ��̬����
    30.0f,              // �¶ȱ�����ֵ
    90};                // �����ʼ�Ƕ�
// �鿴MPU6050��ʼ��״̬
uint8_t init_status;
/**
 * @brief  ϵͳ��ʼ��
 * @param  None
 * @retval None
 */
void System_Init(void)
{

  // ��ʼ����������
  OLED_Init();
  Servo_Init();
  Encoder_Init();
  init_status = MPU6050_Init();
  OLED_Clear();
  if (init_status != 0)
  {
    OLED_ShowString(1, 1, "MPU6050 Error!");
    // ��ʾMPU6050��ID ���ID��ȡ������FF�����ʾI2C��������ʧ��
    OLED_ShowHexNum(2, 1, MPU6050_ReadID(), 2);
    while (1)
      ;
  }
  // LED�Լ�
  LED_AllOn();
  HAL_Delay(500);
  LED_AllOff();

  // OLED��ʾ��ӭ��Ϣ
  OLED_Clear();
  OLED_ShowString(1, 1, "System Init...");
  OLED_ShowString(2, 1, "Welcome!");
  HAL_Delay(1000);

  // ����ϵͳ״̬
  systemState.isInitialized = 1;
  System_SetMode(SYS_MODE_MONITOR);
}

/**
 * @brief  ϵͳ��������
 * @param  None
 * @retval None
 */
void System_Process(void)
{
  // ���´���������
  systemState.temperature = TempSensor_GetTemp();
  systemState.lightLevel = LightSensor_GetPercent();
  MPU6050_GetAttitude(&systemState.attitude);

  // �����û�����
  System_HandleInput();

  // ��鱨������
  System_CheckAlarm();

  // ������ʾ
  System_UpdateDisplay();


  // ϵͳ����ָʾ
  LED_SystemRunning();
}

/**
 * @brief  ����ϵͳģʽ
 * @param  mode: Ŀ��ģʽ
 * @retval None
 */
void System_SetMode(SystemMode mode)
{
  systemState.mode = mode;

  // ��������ʾģʽ����
  OLED_Clear();
  switch (mode)
  {
  case SYS_MODE_MONITOR:
    OLED_ShowString(1, 1, "Monitor Mode");
    LED_Off(LED1_Pin | LED3_Pin);
    OLED_Clear();
    break;

  case SYS_MODE_SETTING:
    OLED_ShowString(1, 1, "Setting Mode");
    LED_On(LED2_Pin);
    LED_Off(LED3_Pin);
    OLED_Clear();
    break;

  case SYS_MODE_DEBUG:
    OLED_ShowString(1, 1, "Debug Mode");
    LED_On(LED3_Pin);
    LED_Off(LED2_Pin);
    OLED_Clear();
    break;
  }
  HAL_Delay(500);
}

/**
 * @brief  ������ʾ
 * @param  None
 * @retval None
 */
void System_UpdateDisplay(void)
{
  switch (systemState.mode)
  {
  case SYS_MODE_MONITOR:
    // ��ʾ���д���������
    OLED_ShowString(1, 1, "Temp:");
    OLED_ShowNum(1, 6, (uint16_t)systemState.temperature, 2);
    OLED_ShowString(1, 8, ".");
    OLED_ShowNum(1, 9, (uint16_t)(systemState.temperature * 10) % 10, 1);

    OLED_ShowString(2, 1, "Light:");
    OLED_ShowNum(2, 7, systemState.lightLevel, 3);
    OLED_ShowString(2, 10, "%");

    OLED_ShowString(3, 1, "Pitch:");
    OLED_ShowSignedNum(3, 7, (int16_t)systemState.attitude.pitch, 3);

    OLED_ShowString(4, 1, "Roll:");
    OLED_ShowSignedNum(4, 6, (int16_t)systemState.attitude.roll, 3);
    break;

  case SYS_MODE_SETTING:
    // ��ʾ���ò���
    OLED_ShowString(2, 1, "Temp Threshold:");
    OLED_ShowNum(2, 15, (uint16_t)systemState.tempThreshold, 2);

    OLED_ShowString(3, 1, "Servo Angle:");
    OLED_ShowNum(3, 13, systemState.servoAngle, 3);
    break;

  case SYS_MODE_DEBUG:
    // ��ʾ������Ϣ
    OLED_ShowString(1, 1, "Debug Mode");
    OLED_ShowNum(2, 1, (uint16_t)systemState.tempThreshold, 2);
    OLED_ShowNum(3, 1, (uint16_t)Encoder_GetCount(), 3);
    break;
  }
}

/**
 * @brief  ��鱨������
 * @param  None
 * @retval None
 */
void System_CheckAlarm(void)
{
  // ����¶��Ƿ񳬹���ֵ
  if (systemState.temperature > systemState.tempThreshold)
  {
    if (!systemState.isAlarming)
    {
      systemState.isAlarming = 1;
      // ���ת��
      Servo_Running();
      Beeper_Beep(500); // ����������
    }
    LED_AlarmStatus(); // LED��˸
  }
  else
  {
    systemState.isAlarming = 0;
    LED_Off(LED4_Pin);
  }
}

/**
 * @brief  �����û�����
 * @param  None
 * @retval None
 */
void System_HandleInput(void)
{
  static ButtonState ModeButton_lastState = BTN_IDLE,
                     ConfirmButton_lastState = BTN_IDLE,
                     AlarmButton_lastState = BTN_IDLE,
                     ResetButton_lastState = BTN_IDLE;
  ButtonState ModeButton_btnState, ConfirmButton_btnState,
      AlarmButton_btnState,
      ResetButton_btnState;
  EncoderState encState;
  static uint8_t alarm_flag = 0;

  // ɨ�谴��
  Button_Scan();
  // ��ȡ���а���״̬
  ModeButton_btnState = Button_GetState(KEY_MODE);
  ConfirmButton_btnState = Button_GetState(KEY_CONFIRM);
  AlarmButton_btnState = Button_GetState(KEY_ALARM);
  ResetButton_btnState = Button_GetState(KEY_RESET);
  // �����һ��������״̬Ϊ�̰���������һ��״̬���Ƕ̰������л�ģʽ
  if (ModeButton_btnState == BTN_SHORT_PRESS && ModeButton_lastState != BTN_SHORT_PRESS)
  {
    // �л�ģʽ
    switch (systemState.mode)
    {
    case SYS_MODE_MONITOR:
      System_SetMode(SYS_MODE_SETTING);
      break;
    case SYS_MODE_SETTING:
      System_SetMode(SYS_MODE_DEBUG);
      break;
    case SYS_MODE_DEBUG:
      System_SetMode(SYS_MODE_MONITOR);
      break;
    }
  }

  // ����ڶ���������״̬Ϊ�̰���������һ��״̬���Ƕ̰�����ȷ������
  if (ConfirmButton_btnState == BTN_SHORT_PRESS && ConfirmButton_lastState != BTN_SHORT_PRESS)
  {
    // ��������ģʽ�£���ȷ������ֵ
    if (systemState.mode == SYS_MODE_SETTING)
    {
      // ֱ��ת�ؼ��ģʽ
      System_SetMode(SYS_MODE_MONITOR);
    }
  }
  // ���������������״̬Ϊ�̰���������һ��״̬���Ƕ̰������л�ģʽ
  if (AlarmButton_btnState == BTN_SHORT_PRESS && AlarmButton_lastState != BTN_SHORT_PRESS){
    if(alarm_flag)
      alarm_flag = 0;
    else
      alarm_flag = 1;
  }

  // ���µ��ĸ���ť������ֵ��λ
  if (ResetButton_btnState == BTN_SHORT_PRESS && ResetButton_lastState != BTN_SHORT_PRESS)
  {
    MPU6050_Attitude defaultAttitude = {0.0f, 0.0f, 0.0f};
    systemState.attitude = defaultAttitude;
    systemState.isAlarming = 0;
    systemState.isInitialized = 1;
    systemState.lightLevel = 0;
    systemState.servoAngle = 90;
    systemState.temperature = 0.0f;
    systemState.tempThreshold = 30.0f;
    System_SetMode(SYS_MODE_MONITOR);
    OLED_Clear();
  }

  // ������ģʽ�£�ʹ�ñ��������ڲ���
  if (systemState.mode == SYS_MODE_SETTING)
  {
    encState = Encoder_GetState();
    // ���������־Ϊ1������ڶ���Ƕ�
    if (alarm_flag)
    {
      // ���ڶ���Ƕ�
      if (encState == ENCODER_CW)
      {
        systemState.servoAngle += 1;
        if (systemState.servoAngle > 180)
          systemState.servoAngle = 180;
      }
      else if (encState == ENCODER_CCW)
      {
        systemState.servoAngle -= 1;
        if (systemState.servoAngle == 0)
          systemState.servoAngle = 0;
      }
    }
    else
    {
      // �����¶��ż�
      if (encState == ENCODER_CW)
      {
        systemState.tempThreshold += 0.5f;
        if (systemState.tempThreshold > 50.0f)
          systemState.tempThreshold = 50.0f;
      }
      else if (encState == ENCODER_CCW)
      {
        systemState.tempThreshold -= 0.5f;
        if (systemState.tempThreshold < 0.0f)
          systemState.tempThreshold = 0.0f;
      }
    }
  }

  // ���°���״̬
  ModeButton_lastState = ModeButton_btnState;
  ConfirmButton_lastState = ConfirmButton_btnState;
  AlarmButton_lastState = AlarmButton_btnState;
  ResetButton_lastState = ResetButton_btnState;
}

/**
 * @brief  ��ȡϵͳ״̬
 * @param  None
 * @retval SystemState*: ϵͳ״ָ̬��
 */
SystemState *System_GetState(void)
{
  return &systemState;
}

/**
  * @brief  ������ֵ����ת�����
  * @param  None
  * @retval None
  */
void Servo_Running(void){
  if(systemState.temperature > systemState.tempThreshold)
    Servo_SetAngle(systemState.servoAngle);
  else
    Servo_SetAngle(90);
}
