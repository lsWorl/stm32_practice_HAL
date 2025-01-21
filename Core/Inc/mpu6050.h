#ifndef __MPU6050_H
#define __MPU6050_H
#include "i2c.h"
#include "gpio.h"
#include "stm32f1xx_hal.h"  // ���� HAL ��ͷ�ļ�
// MPU6050�Ĵ�����ַ����
#define MPU_ADDR            0x68    // MPU6050������ַ
#define MPU_SELF_TESTX_REG 0x0D    // �Լ�Ĵ���X
#define MPU_SELF_TESTY_REG 0x0E    // �Լ�Ĵ���Y
#define MPU_SELF_TESTZ_REG 0x0F    // �Լ�Ĵ���Z
#define MPU_SELF_TESTA_REG 0x10    // �Լ�Ĵ���A
#define MPU_SAMPLE_RATE_REG 0x19    // ����Ƶ�ʷ�Ƶ��
#define MPU_CFG_REG        0x1A    // ���üĴ���
#define MPU_GYRO_CFG_REG   0x1B    // ���������üĴ���
#define MPU_ACCEL_CFG_REG  0x1C    // ���ٶȼ����üĴ���
#define MPU_MOTION_DET_REG 0x1F    // �˶���ֵⷧ���üĴ���
#define MPU_FIFO_EN_REG    0x23    // FIFOʹ�ܼĴ���
#define MPU_I2CMST_CTRL_REG 0x24   // IIC�������ƼĴ���
#define MPU_I2CSLV0_ADDR_REG 0x25  // IIC�ӻ�0������ַ�Ĵ���
#define MPU_I2CSLV0_REG    0x26    // IIC�ӻ�0���ݵ�ַ�Ĵ���
#define MPU_I2CSLV0_CTRL_REG 0x27  // IIC�ӻ�0���ƼĴ���
#define MPU_I2CSLV1_ADDR_REG 0x28  // IIC�ӻ�1������ַ�Ĵ���
#define MPU_I2CSLV1_REG    0x29    // IIC�ӻ�1���ݵ�ַ�Ĵ���
#define MPU_I2CSLV1_CTRL_REG 0x2A  // IIC�ӻ�1���ƼĴ���
#define MPU_I2CSLV2_ADDR_REG 0x2B  // IIC�ӻ�2������ַ�Ĵ���
#define MPU_I2CSLV2_REG    0x2C    // IIC�ӻ�2���ݵ�ַ�Ĵ���
#define MPU_I2CSLV2_CTRL_REG 0x2D  // IIC�ӻ�2���ƼĴ���
#define MPU_I2CSLV3_ADDR_REG 0x2E  // IIC�ӻ�3������ַ�Ĵ���
#define MPU_I2CSLV3_REG    0x2F    // IIC�ӻ�3���ݵ�ַ�Ĵ���
#define MPU_I2CSLV3_CTRL_REG 0x30  // IIC�ӻ�3���ƼĴ���
#define MPU_I2CSLV4_ADDR_REG 0x31  // IIC�ӻ�4������ַ�Ĵ���
#define MPU_I2CSLV4_REG    0x32    // IIC�ӻ�4���ݵ�ַ�Ĵ���
#define MPU_I2CSLV4_DO_REG 0x33    // IIC�ӻ�4д���ݼĴ���
#define MPU_I2CSLV4_CTRL_REG 0x34  // IIC�ӻ�4���ƼĴ���
#define MPU_I2CSLV4_DI_REG 0x35    // IIC�ӻ�4�����ݼĴ���
#define MPU_I2CMST_STA_REG 0x36    // IIC����״̬�Ĵ���
#define MPU_INTBP_CFG_REG  0x37    // �ж�/��·���üĴ���
#define MPU_INT_EN_REG     0x38    // �ж�ʹ�ܼĴ���
#define MPU_INT_STA_REG    0x3A    // �ж�״̬�Ĵ���
#define MPU_ACCEL_XOUTH_REG 0x3B   // ���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_XOUTL_REG 0x3C   // ���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_YOUTH_REG 0x3D   // ���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_YOUTL_REG 0x3E   // ���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_ZOUTH_REG 0x3F   // ���ٶ�ֵ,Z���8λ�Ĵ���
#define MPU_ACCEL_ZOUTL_REG 0x40   // ���ٶ�ֵ,Z���8λ�Ĵ���
#define MPU_TEMP_OUTH_REG  0x41    // �¶�ֵ��8λ�Ĵ���
#define MPU_TEMP_OUTL_REG  0x42    // �¶�ֵ��8λ�Ĵ���
#define MPU_GYRO_XOUTH_REG 0x43    // ������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_XOUTL_REG 0x44    // ������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_YOUTH_REG 0x45    // ������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_YOUTL_REG 0x46    // ������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_ZOUTH_REG 0x47    // ������ֵ,Z���8λ�Ĵ���
#define MPU_GYRO_ZOUTL_REG 0x48    // ������ֵ,Z���8λ�Ĵ���
#define MPU_PWR_MGMT1_REG  0x6B    // ��Դ����Ĵ���1
#define MPU_PWR_MGMT2_REG  0x6C    // ��Դ����Ĵ���2
#define MPU_WHO_AM_I_REG   0x75    // ����ID�Ĵ���

// ��̬���ݽṹ��
typedef struct {
    float pitch;    // ������
    float roll;     // �����
    float yaw;      // ƫ����
} MPU6050_Attitude;

// MPU6050����
uint8_t MPU6050_Init(void);                    // ��ʼ��MPU6050
uint8_t MPU6050_ReadID(void);                  // ��ȡMPU6050��ID
void MPU6050_GetData(short *accx, short *accy, short *accz,
                     short *gyrox, short *gyroy, short *gyroz); // ��ȡԭʼ����
void MPU6050_GetAttitude(MPU6050_Attitude *attitude); // ��ȡ��̬�Ƕ�

#endif
