#include "OLED.h"  // 包含 OLED 头文件
#include "OLED_Font.h"
// 定义 OLED 的 I2C 句柄
extern I2C_HandleTypeDef hi2c1;  // 由 STM32CubeMX 生成

/**
  * @brief  OLED 写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void OLED_WriteCommand(uint8_t Command)
{
    uint8_t data[2] = {0x00, Command};  // 0x00 表示写命令
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDRESS, data, 2, HAL_MAX_DELAY);
}

/**
  * @brief  OLED 写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void OLED_WriteData(uint8_t Data)
{
    uint8_t data[2] = {0x40, Data};  // 0x40 表示写数据
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDRESS, data, 2, HAL_MAX_DELAY);
}

/**
  * @brief  OLED 设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    OLED_WriteCommand(0xB0 | Y);  // 设置 Y 位置
    OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));  // 设置 X 位置高 4 位
    OLED_WriteCommand(0x00 | (X & 0x0F));  // 设置 X 位置低 4 位
}

/**
  * @brief  OLED 清屏
  * @param  无
  * @retval 无
  */
void OLED_Clear(void)
{
    uint8_t i, j;
    for (j = 0; j < OLED_PAGE_NUM; j++)
    {
        OLED_SetCursor(j, 0);
        for (i = 0; i < OLED_WIDTH; i++)
        {
            OLED_WriteData(0x00);  // 清空显示
        }
    }
}

/**
  * @brief  OLED 显示一个字符
  * @param  Line 行位置，范围：1~4
  * @param  Column 列位置，范围：1~16
  * @param  Char 要显示的一个字符，范围：ASCII 可见字符
  * @retval 无
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    uint8_t i;
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);  // 设置光标位置在上半部分
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i]);  // 显示上半部分内容
    }
    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);  // 设置光标位置在下半部分
    for (i = 0; i < 8; i++)
    {
        OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);  // 显示下半部分内容
    }
}

/**
  * @brief  OLED 显示字符串
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，范围：ASCII 可见字符
  * @retval 无
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++)
    {
        OLED_ShowChar(Line, Column + i, String[i]);
    }
}

/**
  * @brief  OLED 次方函数
  * @param  X 基数
  * @param  Y 指数
  * @retval 返回值等于 X 的 Y 次方
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--)
    {
        Result *= X;
    }
    return Result;
}

/**
  * @brief  OLED 显示数字（十进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
  * @brief  OLED 显示数字（十进制，带符号数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
    uint8_t i;
    uint32_t Number1;
    if (Number >= 0)
    {
        OLED_ShowChar(Line, Column, '+');
        Number1 = Number;
    }
    else
    {
        OLED_ShowChar(Line, Column, '-');
        Number1 = -Number;
    }
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
  * @brief  OLED 显示数字（十六进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval 无
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i, SingleNumber;
    for (i = 0; i < Length; i++)
    {
        SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
        if (SingleNumber < 10)
        {
            OLED_ShowChar(Line, Column + i, SingleNumber + '0');
        }
        else
        {
            OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
        }
    }
}

/**
  * @brief  OLED 显示数字（二进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
    }
}

/**
  * @brief  OLED 初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{

    // 初始化 OLED
    OLED_WriteCommand(0xAE);  // 关闭显示
    OLED_WriteCommand(0xD5);  // 设置显示时钟分频比/振荡器频率
    OLED_WriteCommand(0x80);
    OLED_WriteCommand(0xA8);  // 设置多路复用率
    OLED_WriteCommand(0x3F);
    OLED_WriteCommand(0xD3);  // 设置显示偏移
    OLED_WriteCommand(0x00);
    OLED_WriteCommand(0x40);  // 设置显示开始行
    OLED_WriteCommand(0xA1);  // 设置左右方向，0xA1 正常
    OLED_WriteCommand(0xC8);  // 设置上下方向，0xC8 正常
    OLED_WriteCommand(0xDA);  // 设置 COM 引脚硬件配置
    OLED_WriteCommand(0x12);
    OLED_WriteCommand(0x81);  // 设置对比度控制
    OLED_WriteCommand(0xCF);
    OLED_WriteCommand(0xD9);  // 设置预充电周期
    OLED_WriteCommand(0xF1);
    OLED_WriteCommand(0xDB);  // 设置 VCOMH 取消选择级别
    OLED_WriteCommand(0x30);
    OLED_WriteCommand(0xA4);  // 设置整个显示打开/关闭
    OLED_WriteCommand(0xA6);  // 设置正常/倒转显示
    OLED_WriteCommand(0x8D);  // 设置充电泵
    OLED_WriteCommand(0x14);
    OLED_WriteCommand(0xAF);  // 开启显示

    OLED_Clear();  // 清屏
}
