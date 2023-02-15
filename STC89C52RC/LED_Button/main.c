#include <REGX52.H>
#include <INTRINS.H>

void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void Delay1ms(unsigned int xms)		//@12.000MHz
{
	do
	{
		unsigned char i, j;

		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}while (--xms);
}

void Flash() // ��˸
{
	while (1)
	{	
		P1 = 0xFE;
		Delay500ms();
		P1 = 0xFF;
		Delay500ms();
	}
}

void Gradient1() // ��ˮ��1  ����
{
	do
	{
		unsigned char i;
		P1 = 0xFF;
		i = 0x01;
		while (i != 0x00)
		{
			P1 = P1 ^ i;  // 0xFF->0x00->0xFF
			i = i << 1;
			Delay500ms();
		}
	}while (1);
}

void Gradient2()  // ��ˮ��2  ��λ����
{
	do
	{
		P1 = 0xFE;
		while (P1 != 0xFF)
		{
			Delay1ms(100);
			P1 = ~((~P1) << 1);  
		}
	}while (1);
}

void Button1()  // ��ť ��ס����
{
	while (1)
	{
		if (P3_5 == 0)  // ���°�ťS1�������
		{
			P1_0 = 0;
		}
		else
		{
			P1_0 = 1;   // ��������
		}
	}
}

void Button2()  // ��һ�� ���� / ��
{
	while (1)
	{
		if (P3_5 == 0)
		{
			Delay1ms(20);  // ���� ��ʱ20ms
			while (P3_5 == 0) ;  // �����ڼ�ȴ�
			Delay1ms(20);
			
			P1_0 = ~P1_0;   // ����->ȡ��->��/��
		}
	}
}

void Button3()  // �����ư�ť���
{
	unsigned char LEDNum = 0;
	
	while (1)
	{
		if (P3_5 == 0)
		{
			Delay1ms(250);  // ���� 250ms��Ϊ�����ֳ����Ͷ̰�
			while (P3_5 == 0)  
			{
				Delay1ms(20);
				if (P3_5 == 0)   // ���� һֱ��λ
				{
					++LEDNum;
					P1 =  ~LEDNum;
				}
				Delay1ms(20);				
			}
			Delay1ms(20);
			
			// �̰� ÿ�ν�һλ
			++LEDNum;
			P1 =  ~LEDNum;
		}
	}
}

void Button4()  // ��ť����LED������λ
{
	unsigned char LEDNum = 0;
	P1 = 0xFE;   // 
	
	while (1)
	{
		if (P3_5 == 0)
		{
			Delay1ms(250);  // ���� 250ms��Ϊ�����ֳ����Ͷ̰�
			
			while (P3_5 == 0)  
			{
				Delay1ms(100);  // ����
				
				if (P3_5 == 0)
				{
					// ���� һֱ��λ				
					++LEDNum;   
					if (LEDNum >= 8)
					{
						LEDNum = 0;
					}
					P1 =  ~(0x01 << LEDNum);	
				}
				
				Delay1ms(20);				
			}
			
			Delay1ms(20);
			
			// �̰� ÿ����һλ
			++LEDNum;
			if (LEDNum >= 8)
			{
				LEDNum = 0;
			}
			P1 =  ~(0x01 << LEDNum);	
		}
		
		if (P3_4 == 0)
		{
			Delay1ms(250);  // ���� 250ms��Ϊ�����ֳ����Ͷ̰�
			
			while (P3_4 == 0)  
			{
				Delay1ms(100);  // ����
				
				if (P3_4 == 0)
				{
					// ���� һֱ��λ
					if (LEDNum == 0)
					{
						LEDNum = 7;
					}
					else
					{
						--LEDNum;
					}
					P1 =  ~(0x01 << LEDNum);
				}
				
				Delay1ms(20);				
			}
			
			Delay1ms(20);
			
			// �̰� ÿ����һλ
			if (LEDNum == 0)
			{
				LEDNum = 7;
			}
			else
			{
				--LEDNum;
			}
			P1 =  ~(0x01 << LEDNum);
		}
	}
}


void main()
{
	// P1 = 0xFE; // 1111 1110 ��������LED
	// P1 = 0xAA; // 1010 1010 ���


	// Flash();  // ��˸
	// Gradient1();  // ����
	// Gradient2();  // ��λ����
	// Button1();  // ��סS1����
	// Button2();  // ����->ȡ��->��/��
	// Button3();   // �����Ƶ��
	Button4();   // LED������λ
	
}