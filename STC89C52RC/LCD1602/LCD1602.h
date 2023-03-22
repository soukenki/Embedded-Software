#ifndef __LCD1602_H__
#define __LCD1602_H__

// ��Ļ 16*2
// DDRAM 40*2

// ��ʱ
void Delay1ms(int num);

// дָ��
void LCD_WriteCommand(unsigned char command);
// д����
void LCD_WriteData(unsigned char val);

// ��ʼ��
void LCD_Init();

// ��ӡ�ַ�
void LCD_ShowChar(unsigned char line, unsigned char column, unsigned char val);
// ��ӡ�ַ���
void LCD_ShowArray(unsigned char line, unsigned char column, unsigned char* arr);
// ��ӡ�з�����
void LCD_ShowNum(unsigned char line, unsigned char column, int num, unsigned char len);
// ��ӡ�޷�����
void LCD_ShowSignedNum(unsigned char line, unsigned char column, int num, unsigned char len);
// ��ӡʮ��������
void LCD_ShowHexNum(unsigned char line, unsigned char column, int num, unsigned char len);
// ��ӡ��������
void LCD_ShowBitNum(unsigned char line, unsigned char column, int num, unsigned char len);

#endif