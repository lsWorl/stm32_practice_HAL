#include "mpu6050.h"
#include <math.h>

// ����MPU6050�ڲ��Ĵ�����ʼ������
static const uint8_t MPU_Init_Data[][2] = {
    {MPU_PWR_MGMT1_REG, 0x00},   // �������״̬
    {MPU_SAMPLE_RATE_REG, 0x07}, // �����ʣ�1000/(1+7)=125Hz
    {MPU_CFG_REG, 0x06},         // �������ֵ�ͨ�˲���
    {MPU_GYRO_CFG_REG, 0x18},    // �������Լ켰������Χ����2000dps
    {MPU_ACCEL_CFG_REG, 0x00}    // ���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ���2g
};

// ����MPU6050���ݻ���
static short gyro[3], accel[3]; // �����Ǻͼ��ٶȼ����ݻ���

/**
 * @brief  ��ʼ��MPU6050
 * @param  None
 * @retval 0:�ɹ� 1:ʧ��
 */
uint8_t MPU6050_Init(void)
{
  uint8_t i;

  // ���MPU6050�Ƿ�����
  if (MPU6050_ReadID() != 0x68) // ��ȡMPU6050��ID�����ID����ȷ������1
    return 1;

  // ����MPU6050�ڲ��Ĵ���
  for (i = 0; i < sizeof(MPU_Init_Data) / 2; i++) // sizeof(MPU_Init_Data)/2��ֵΪ5
  {
    HAL_I2C_Mem_Write(&hi2c2, MPU_ADDR << 1, MPU_Init_Data[i][0], I2C_MEMADD_SIZE_8BIT, (uint8_t *)&MPU_Init_Data[i][1], 1, HAL_MAX_DELAY);
    HAL_Delay(5);
  }

  return 0;
}

/**
 * @brief  ��ȡMPU6050��ID
 * @param  None
 * @retval IDֵ
 */
uint8_t MPU6050_ReadID(void)
{
  uint8_t id;
  HAL_I2C_Mem_Read(&hi2c2, MPU_ADDR << 1, MPU_WHO_AM_I_REG, I2C_MEMADD_SIZE_8BIT, &id, 1, HAL_MAX_DELAY);
  return id;
}

/**
 * @brief  ��ȡMPU6050��ԭʼ����
 * @param  accx,accy,accz:���ٶȼ�x,y,z���ԭʼ����(������)
 * @param  gyrox,gyroy,gyroz:������x,y,z���ԭʼ����(������)
 * @retval None
 */
void MPU6050_GetData(short *accx, short *accy, short *accz,
                     short *gyrox, short *gyroy, short *gyroz)
{
  uint8_t buf[14];

  // ��ȡ���ٶȺ������ǵ�ԭʼ����
  HAL_I2C_Mem_Read(&hi2c2, MPU_ADDR << 1, MPU_ACCEL_XOUTH_REG, I2C_MEMADD_SIZE_8BIT, buf, 14, HAL_MAX_DELAY);

  // �ϳ�����
  *accx = ((uint16_t)buf[0] << 8) | buf[1];
  *accy = ((uint16_t)buf[2] << 8) | buf[3];
  *accz = ((uint16_t)buf[4] << 8) | buf[5];
  *gyrox = ((uint16_t)buf[8] << 8) | buf[9];
  *gyroy = ((uint16_t)buf[10] << 8) | buf[11];
  *gyroz = ((uint16_t)buf[12] << 8) | buf[13];
}

/**
 * @brief  ��ȡMPU6050����̬�Ƕ�
 * @param  attitude: ��̬�ǶȽṹ��ָ��
 * @retval None
 */
void MPU6050_GetAttitude(MPU6050_Attitude *attitude)
{
  float ax, ay, az;

  // ��ȡԭʼ����
  MPU6050_GetData(&accel[0], &accel[1], &accel[2],
                  &gyro[0], &gyro[1], &gyro[2]);

  // ת��Ϊʵ�ʵ�gֵ�����������ǡ�2g
  ax = accel[0] / 16384.0f;
  ay = accel[1] / 16384.0f;
  az = accel[2] / 16384.0f;

  // ���ݼ��ٶȼ���Ƕ�
  attitude->pitch = atan2f(ax, sqrtf(ay * ay + az * az)) * 57.3f;
  attitude->roll = atan2f(ay, az) * 57.3f;

  // ƫ������Ҫ�شż���ϣ������ݲ�����
  attitude->yaw = 0;
}
