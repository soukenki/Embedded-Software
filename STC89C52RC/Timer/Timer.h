#ifndef __Timer_H__
#define __Timer_H__

#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"

// ��ʼ����ʱ��
void Timer0_Init();

// ������������
unsigned char Key();

// 1ms�ȴ�@11.0592MHz (��LCD�е���ʱ������ͻ������ע�͵�)
//void Delay1ms(unsigned int xms);	

// ���Զ�����ť
void testTimer1();

// ���Զ�������������ˮ�ƣ���ʱ��ʵ�֣�
void testTimer2();

// ����LCDʱ�ӣ���ʱ��ʵ�֣�
void testTimer3();

#endif