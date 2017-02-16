#include "song_spi.h"

void SSPIInit()
{
	GPIO_InitTypeDef sgpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);
	sgpio.GPIO_Mode = GPIO_Mode_Out_PP; 
	sgpio.GPIO_Speed = GPIO_Speed_10MHz;
	sgpio.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &sgpio);

	sgpio.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_9  ;
	GPIO_Init(GPIOC,&sgpio);

	sgpio.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_9;
	GPIO_Init(GPIOB, &sgpio);

	sgpio.GPIO_Mode = GPIO_Mode_IPU;
	sgpio.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB, &sgpio);
	

	ADC = 1;
	DAC = 1;
}

u16  SSPIADCRead()
{
	u16 tmp = 0;
	u8 i;
	ADC = 1;
	SADCLK = 1;
	ADC = 0;
	for (i = 0; i < 15; i++)
	{
		tmp <<= 1;
		SADCLK = 0;//此时读到的是上一个循环的值。
		if (SDAADC) tmp++;
		SADCLK = 1;
	}
	tmp >>= 2;
	ADC = 1;
	return tmp;
}

void SSPIDACWrite(u16 com)
{
	u8 i;
	CLK = 1;
	DAC = 0;
	for (i = 0; i < 16; i++)
	{
		if (com & 0x80)
			SDADAC = 1;
		else
		{
			SDADAC = 0;
		}
		com <<= 1;
		CLK = 0;
		CLK = 1;
	}
	DAC = 1;
}

