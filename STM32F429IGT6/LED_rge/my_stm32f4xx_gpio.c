
#include "my_stm32f4xx_gpio.h"


/* �������� �ߵ�ƽ
 * GPIOx��GPIO�˿ں�     GPIO_Pin���˿ڵ����ź�
 */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BSRRL |= (1 << GPIO_Pin);
}

// ��λ���� �͵�ƽ
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIOx->BSRRH |= (1 << GPIO_Pin);
}

// ��ʼ��
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_IninTyeDef *GPIO_InitStruct)
{
	// ���ҵ����ź�
	for (uint32_t pinpos = 0x00; pinpos < 16; pinpos++)
	{
		uint32_t pos = ((uint16_t)0x01) << pinpos;
		uint32_t currentpos = pos & GPIO_InitStruct->GPIO_Pin;
		
		if (currentpos == pos)
		{
			GPIOx->MODER &= ~(3 << (2 * pinpos));
			GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (2 * pinpos));
		
			GPIOx->PUPDR &= ~(3 << (2 * pinpos));
			GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (2 * pinpos));
		
			if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
			{
				GPIOx->OSPEEDR &= ~(3 << (2 * pinpos));
				GPIOx->OSPEEDR |= (((uint32_t)GPIO_InitStruct->GPIO_Speed) << (2 * pinpos));
			}
			
			GPIOx->OTYPER &= ~(1 << pinpos);
			GPIOx->OTYPER |= (((uint16_t)GPIO_InitStruct->GPIO_OType) << (pinpos));
		}
	}
}

