#include "Timer.h"
 
unsigned char LEDMode = 0;
unsigned char Sec, Min, Hour;

// 1ms�ȴ�@11.0592MHz  (��LCD�е���ʱ������ͻ������ע�͵�)
//void Delay1ms(unsigned int xms)
//{
//	do
//	{
//		unsigned char i, j;

//		i = 2;
//		j = 199;
//		do
//		{
//			while (--j);
//		} while (--i);
//	}while (--xms);
//}

// ������������  ��Χ0~4  �ް�������ʱ������0
unsigned char Key()
{
	unsigned char KeyNum = 0;
	if (P3_5 == 0)
	{
		Delay1ms(20);
		while (P3_5 == 0);
		Delay1ms(20);
		KeyNum = 1;
	}
	
	if (P3_4 == 0)
	{
		Delay1ms(20);
		while (P3_4 == 0);
		Delay1ms(20);
		KeyNum = 2;
	}
	
	if (P3_3 == 0)
	{
		Delay1ms(20);
		while (P3_3 == 0);
		Delay1ms(20);
		KeyNum = 3;
	}
	
	if (P3_2 == 0)
	{
		Delay1ms(20);
		while (P3_2 == 0);
		Delay1ms(20);
		KeyNum = 4;
	}
	return KeyNum;
}

// ��ʼ����ʱ��
void Timer0_Init()     // 1����@11.0592MHz
{
	//TMOD = 0x01;  // 0000 0001
	TMOD &= 0xF0;  // ��TMTD�ĵ�4λ���㣬��4λ���ֲ���
	TMOD |= 0x01;  // ��TMTD�ĵ�4λ��Ϊ1����4λ���ֲ���
	
	TF0 = 0;    // ���TF0��־
	TR0 = 1;    // ��ʱ��0��ʼ��ʱ
	
	// TH0 = 64535/256+1;   // 0x18
	// TL0 = 64535%256+1;   // 0xFC
	TL0 = 0x18;		// ���ö�ʱ��ֵ
	TH0 = 0xFC;		// ���ö�ʱ��ֵ
	
	// �����ж�
	ET0 = 1;
	EA = 1;
	PT0 = 0;

}

// �ж� (������ˮ��)
void Timer0_Routine1() interrupt 2
{
	static unsigned int T0Count = 0;
	
	TL0 = 0x18;		// ���ö�ʱ��ֵ
	TH0 = 0xFC;		// ���ö�ʱ��ֵ
	
	T0Count++;
	if (T0Count >= 500)  // 0.5��
	{	
		T0Count = 0;
		if (LEDMode == 0)
			P1 = _crol_(P1, 1);  // ѭ������
		if (LEDMode == 1)
			P1 = _cror_(P1, 1);  // ѭ������

	}
}


// ���Զ�����ť
void testTimer1()
{
	unsigned char KeyNum;
	
	while (1)
	{
		KeyNum = Key();
		if (KeyNum)
		{
			if (KeyNum == 1){P1_0 = ~P1_0;}
			if (KeyNum == 2){P1_1 = ~P1_1;}
			if (KeyNum == 3){P1_2 = ~P1_2;}
			if (KeyNum == 4){P1_3 = ~P1_3;}			
		}
	}
}



// ���Զ�������������ˮ�ƣ���ʱ��ʵ�֣�
void testTimer2()
{
	unsigned char KeyNum = 0;

	P1 = 0xFE;
	Timer0_Init();
	while (1)
	{
		KeyNum = Key();
		if (KeyNum)
		{
			if (KeyNum == 1)
			{
				LEDMode++;
				if (LEDMode >= 2)
					LEDMode = 0;
			}
		}
	}
}


// �ж� (����ʱ��)
void Timer0_Routine2() interrupt 1
{
	static unsigned int T0Count = 0;
	
	TL0 = 0x18;		// ���ö�ʱ��ֵ
	TH0 = 0xFC;		// ���ö�ʱ��ֵ
	
	T0Count++;
	if (T0Count >= 1000)  // 1��
	{	
		T0Count = 0;
		Sec++;
		if (Sec >= 60)
		{
			Sec = 0;
			Min++;
			if (Min >= 60)
			{
				Min = 0;
				Hour++;
				if (Hour >= 24)
				{	
					Hour = 0;
				}
			}
		}
	}
}

// ����LCDʱ�ӣ���ʱ��ʵ�֣�
void testTimer3()
{
	LCD_Init();     // LCD��ʼ��
	Timer0_Init();  // ��ʱ����ʼ��
	Sec = 55;
	Min = 59;
	Hour = 23;
	LCD_ShowArray(1, 1, "Clock:");
	LCD_ShowArray(2, 1, "  :  :");
	while (1)
	{
		LCD_ShowNum(2, 1, Hour, 2);
		LCD_ShowNum(2, 4, Min, 2);
		LCD_ShowNum(2, 7, Sec, 2);
	}
}