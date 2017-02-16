#include "song_IO.h"

static  u8 fac_us = 0;
static u16 fac_ms = 0;

void SDelayInit(u8 SYSCLK)
{
	SysTick->CTRL &= 0xfffffffb;
	fac_us = SYSCLK / 8;
	fac_ms = (u16) fac_us * 1000;
}

void SDelayUs(u32 nus)
{
	u32 tmp;
	SysTick->LOAD = nus*fac_us;
	SysTick->VAL = 0x00;
	SysTick->CTRL = 0x01;
	do
	{
		tmp = SysTick->CTRL;
	} while ((tmp & 0x01) && !(tmp&(1 << 16)));
	SysTick->CTRL = 0x00;
	SysTick->VAL = 0x00;
}

void SDelayMs(u32 nms)
{
	u32 tmp;
	SysTick->LOAD = nms*fac_ms;
	SysTick->VAL = 0x00;
	SysTick->CTRL = 0x01;
	do
	{
		tmp = SysTick->CTRL;
	} while ((tmp & 0x01) && !(tmp&(1 << 16)));
	SysTick->CTRL = 0x00;
	SysTick->VAL = 0x00;
}

void STestIOInit()
{
	GPIO_InitTypeDef SGPIO;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	SGPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	SGPIO.GPIO_Pin = GPIO_Pin_1;
	SGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &SGPIO);
}

void SClockInit(u8 pll)
{
	unsigned char temp = 0;
	

}

void delay_ms(u32 nms)
{
	SDelayMs(nms);
}
void delay_us(u16 nms)
{
	SDelayUs(nms);
}
