#ifndef __MatrixKey_H__
#define __MatrixKey_H__

#include <REGX52.H>
#include "LCD1602.h"



// ��1������1~16
void KeyDown(unsigned char* keynum);

// ��2������1~16
unsigned char MatrixKey();


// ������
void Password(unsigned char* keynum);

#endif