#include "MatrixKey.h"

#define GPIO_KEY P1



// ��1��1~16
void KeyDown(unsigned char* keynum)
{
	char a = 0;
	GPIO_KEY = 0x0F;
	if (GPIO_KEY != 0x0F)  // ��ȡ�����Ƿ���
	{
		Delay(10); // ��ʱ10ms��������
		if (GPIO_KEY != 0x0F)  // �ٴμ�ⰴ��
		{
			// ������
			GPIO_KEY = 0x0F;
			switch (GPIO_KEY)
			{
				case(0x07): 
					*keynum = 16; break;
				case(0x0B): 
					*keynum = 12; break;
				case(0x0D): 
					*keynum = 8; break;
				case(0x0E): 
					*keynum = 4; break;
			}
			
			// ������
			GPIO_KEY = 0xF0;
			switch (GPIO_KEY)
			{
				case(0x70): 
					*keynum = *keynum; break;
				case(0xB0): 
					*keynum = *keynum-1; break;
				case(0xD0): 
					*keynum = *keynum-2; break;
				case(0xE0): 
					*keynum = *keynum-3; break;
			}
			
			while ((a < 50) && (GPIO_KEY != 0xF0))  // ��ⰴ������
			{
				Delay(10);
				a++;
			}
		}
	}
}


// ��2��1~16

unsigned char MatrixKey()

{
	unsigned char KeyNumber=0;
	
	P1=0xFF;
	P1_3=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=16;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=15;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=14;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=13;}
	
	P1=0xFF;
	P1_2=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=12;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=11;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=10;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=9;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=8;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=7;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=6;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=5;}
	
	P1=0xFF;
	P1_0=0;
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=4;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=3;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=2;}
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=1;}
	
	return KeyNumber;
}

void Password(unsigned char* keynum)
{
	unsigned int password = 0;  // �������
	unsigned int count = 0;  // ����
	
	while (1)
	{
		*keynum =  MatrixKey();
		if (*keynum)
		{
			if (*keynum <= 10)  // ���S1~S10�������£���������
			{
				if (count < 4)  // 4λ����
				{
					password *= 10;
					password += (*keynum % 10);  // ��ȡһλ����
					count++;
				}
				LCD_ShowNum(2, 1, password, 4); // ������ʾ
			}
			
			if (*keynum == 11)  // ���S11���£�ȷ��
			{
				if (password == 718) // ��ȷ����
				{
					LCD_ShowArray(1, 14, "OK ");
					// ���������ת
					// ....
					password = 0;   // ������������
					count = 0;
					LCD_ShowNum(2, 1, password, 4); // ������ʾ
					Delay(1500);
					LCD_ShowArray(1, 14, "   ");
				}
				else
				{
					LCD_ShowArray(1, 14, "ERR");
					password = 0;   // ������������
					count = 0;
					LCD_ShowNum(2, 1, password, 4); // ������ʾ 
					Delay(1500);
					LCD_ShowArray(1, 14, "   ");
				}
			}
			if (*keynum == 12) // ���S12���£�ȡ��
			{
				password = 0;   // ����
				count = 0;
				LCD_ShowNum(2, 1, password, 4); // ������ʾ 
			}
		}
	}
}