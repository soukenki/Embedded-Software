// �½�����ģ�� �Ĵ�����

#include "my_stm32f4xx.h"

#include "my_stm32f4xx_gpio.h"
#include "bsp_led.h"

// ��ʱ
void LED_Delay(unsigned int count)
{
	for (; count!= 0; count--);
}

// ��ʼ�� �Ĵ�����
void LED_init_GPIOH10_reg(void)
{
	// ����GPIOHʱ��
	RCC_AHB1ENR |= (1 << 7);
	
	// GPIOH10 MODER�Ĵ����ĵ�10λ���
	GPIOH_MODER &= ~(0x03 << (2 * 10));
	// ����PH10��Ϊ���ģʽ
	GPIOH_MODER |= (1 << (2 * 10));
	
	// GPIOH OTYPER�Ĵ���10���
	GPIOH_OTYPER &= ~(1 << (1 * 10));
	// 0b ����ģʽ
	GPIOH_OTYPER |= (0 << (1 * 10));
	
	// GPIOH OSPEEDR�Ĵ���10���
	GPIOH_OSPEEDR &= ~(0x03 << (2 * 10));
	// 0b ����2MHz
	GPIOH_OSPEEDR |= (0 << (2 * 10));
	
	// GPIOH PUPDR�Ĵ���10���
	GPIOH_PUPDR &= ~(0x03 << (2 * 10));
	// 01b ����ģʽ
	GPIOH_PUPDR |= (1 << (2 * 10));
	
}

// ��ʼ�� �Ĵ����Ľṹ���
void LED_init_GPIOH10_str(void)
{
	// ����GPIOHʱ��
	RCC_AHB1ENR |= (1 << 7);
	
	// GPIOH10 MODER�Ĵ����ĵ�10λ���
	GPIOH->MODER &= ~(0x03 << (2 * 10));
	// ����PH10��Ϊ���ģʽ
	GPIOH->MODER |= (1 << (2 * 10));
	
	// GPIOH OTYPER�Ĵ���10���
	GPIOH->OTYPER &= ~(1 << (1 * 10));
	// 0b ����ģʽ
	GPIOH->OTYPER |= (0 << (1 * 10));
	
	// GPIOH OSPEEDR�Ĵ���10���
	GPIOH->OSPEEDR &= ~(0x03 << (2 * 10));
	// 0b ����2MHz
	GPIOH->OSPEEDR |= (0 << (2 * 10));
	
	// GPIOH PUPDR�Ĵ���10���
	GPIOH->PUPDR &= ~(0x03 << (2 * 10));
	// 01b ����ģʽ
	GPIOH->PUPDR |= (1 << (2 * 10));
}

// ����/���
void LED_GPIOH10_(unsigned int num)
{
	if (num)
	{
		// PH10 ODR����͵�ƽ
		GPIOH_ODR &= ~(1 << 10); 
		
		// GPIOH BSRR�Ĵ����� BR10��1��ʹ��������͵�ƽ
		//GPIOH_BSRR |= (1 << 16 << 10);
	}
	else
	{
		// PH10 ODR����ߵ�ƽ
		GPIOH_ODR |= (1 << 10); 
		
		// GPIOH BSRR�Ĵ����� BS10��1��ʹ��������ߵ�ƽ
		//GPIOH_BSRR |= (1 << 10);
	}
}



int main(void)
{
	// LED_init_GPIOH10_reg();
	// LED_init_GPIOH10_str();
	LED_GPIO_Config();
	
	while (1)
	{
		
		//LED_GPIOH10_(1);
		GPIO_SetBits(GPIOH, 10); 
		LED_Delay(0xFFFFF);
	
		//LED_GPIOH10_(0);
		GPIO_ResetBits(GPIOH, 10);
		LED_Delay(0xFFFFF);
	}
		
}
