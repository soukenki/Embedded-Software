#include <REGX52.H>

// �������ã�P0����û���������裬����ֻ��ʾ��һ��ȫ��
// sbit LCD_RS = P0^7;
// sbit LCD_RW = P0^6;
// sbit LCD_E = P0^5;

// �������ã���P3����
sbit LCD_RS = P3^2;  // P32
sbit LCD_RW = P3^1;  // P31
sbit LCD_E = P3^0;   // P30

#define LCD_DataPort P2

// ��ʱ @12.000MHz
void Delay1ms(int num)		
{
	while (num--)
	{
		char i, j;

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

// дָ��
void LCD_WriteCommand(unsigned char command) 
{
	LCD_E = 0;   // ʹ������
	LCD_RS = 0;   // 1Ϊ���ݣ�0Ϊָ��
	LCD_RW = 0;   // 1Ϊ����0Ϊд
	
	LCD_DataPort = command;
	
	LCD_E = 1;
	Delay1ms(1);
	
	LCD_E = 0;
	Delay1ms(1);
}

// д����
void LCD_WriteData(unsigned char val)  
{
	LCD_E = 0;   // ʹ������
	LCD_RS = 1;   
	LCD_RW = 0;
	
	LCD_DataPort = val;
	
	LCD_E = 1;  // ���ø�
	Delay1ms(1);
	
	LCD_E = 0;  // ���õ�
	Delay1ms(1);
}

// ��ʼ��
void LCD_Init()  
{
	LCD_WriteCommand(0x38);  // ��λ���ݽӿڣ�������ʾ��5*7����
	LCD_WriteCommand(0x0C);  // ��ʾ�������أ���˸��
	LCD_WriteCommand(0x06);  // ���ݶ�д�����󣬹���Զ���һ�����治��
	LCD_WriteCommand(0x01);  // ��긴λ������
}

// ��λ����
void LCD_SetCursor(unsigned char line, unsigned char column) 
{
	if (line == 1)
	{
		LCD_WriteCommand(0x80 | (column - 0x01));
	}
	else
	{
		LCD_WriteCommand(0x80 | (column - 0x01) + 0x40);
	}
}

// ��ӡ�ַ�
void LCD_ShowChar(unsigned char line, unsigned char column, unsigned char val)  
{
	LCD_SetCursor(line, column);
	
	LCD_WriteData(val);
}

// ��ӡ�ַ���
void LCD_ShowArray(unsigned char line, unsigned char column, unsigned char* arr)  
{
	unsigned char i = 0;
	
	LCD_SetCursor(line, column);	
	
	for (i = 0; arr[i] != '\0'; ++i)
	{
		LCD_WriteData(arr[i]);
	}
}

// ret = x �� y �η�
int LCD_Pow(int x, int y)  
{
	int i = 0;
	int ret = 1;
	
	for (i = 0; i < y; ++i)
	{
		ret *= x;
	}
	return ret;
}

// ��ӡ�޷�����
void LCD_ShowNum(unsigned char line, unsigned char column, int num, unsigned char len)
{
	unsigned char i = 0;
	
	LCD_SetCursor(line, column);	
	
	for (i = len; i > 0; --i)
	{
		LCD_WriteData('0' + num / LCD_Pow(10, i-1) % 10);
	}
}

// ��ӡ�з�����
void LCD_ShowSignedNum(unsigned char line, unsigned char column, int num, unsigned char len)
{
	unsigned char i = 0;
	unsigned int newnum = 0;
	
	LCD_SetCursor(line, column);	
	
	if (num >= 0)
	{
		LCD_WriteData('+');
		newnum = num;
	}
	else
	{
		LCD_WriteData('-');
		newnum = -num;
	}
	
	for (i = len; i > 0; --i)
	{
		LCD_WriteData('0' + newnum / LCD_Pow(10, i-1) % 10);
	}
}

// ��ӡʮ��������
void LCD_ShowHexNum(unsigned char line, unsigned char column, int num, unsigned char len)
{
	unsigned char i = 0;
	unsigned char single_num = 0;
	
	LCD_SetCursor(line, column);	
	
	for (i = len; i > 0; --i)
	{
		single_num = num / LCD_Pow(16, i-1) % 16;
		if (single_num < 10)
		{
			LCD_WriteData('0' + single_num);
		}
		else
		{
			LCD_WriteData('A' + single_num - 10);
		}		
	}
}

// ��ӡ��������
void LCD_ShowBitNum(unsigned char line, unsigned char column, int num, unsigned char len)
{
	unsigned char i = 0;
	
	LCD_SetCursor(line, column);	
	
	for (i = len; i > 0; --i)
	{
		LCD_WriteData('0' + num / LCD_Pow(2, i-1) % 2);
	}
}

