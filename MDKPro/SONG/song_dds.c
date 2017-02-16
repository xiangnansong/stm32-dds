#include "song_dds.h"
GPIO_InitTypeDef gpio;
void DDSIOInit(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);

	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_0 | GPIO_Pin_1;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_6;
	gpio.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOC, &gpio);

	KEYW = 1;
	KEYR = 1;

}

void DDSAInit()
{
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);

	KEYW = 1;
	KEYR = 1;
}


void DDSWrite(u16 addr, u16 data)
{

	addr <<= 10;
	addr &= 0xfC00;
	GPIOB->ODR &= 0x03ff;
	GPIOB->ODR |= addr;
	DDSWR = 1;
	data &= 0x00ff;
	GPIOA->ODR &= 0xff00;
	GPIOA->ODR |= data;
	DDSWR = 0;
	DDSWR = 1;

}

void DDSConfig(void)
{

	DDSIOInit();
	DDSSR = 0;
	DDSSR = 1;
	SDelayUs(6);
	DDSSR = 0;
	DDSWrite(0x1d, 0x00);
	DDSWrite(0x1e, 0x47);
	DDSWrite(0x1F, 0x01);
	DDSWrite(0x20, 0x20);

}

void DDSWF(unsigned long frequency)
{

	unsigned long long FTW = (281474976710656 / (280000))*frequency;
	DDSWrite(0x04, ((unsigned char*)&FTW)[5]);
	DDSWrite(0x05, ((unsigned char*)&FTW)[4]);
	DDSWrite(0x06, ((unsigned char*)&FTW)[3]);
	DDSWrite(0x07, ((unsigned char*)&FTW)[2]);
	DDSWrite(0x08, ((unsigned char*)&FTW)[1]);
	DDSWrite(0x09, ((unsigned char*)&FTW)[0]);

}


void DDSWA(unsigned long amplitude)
{
	amplitude = (amplitude * 336) / 1000;
	DDSWrite(0x21, amplitude / 256);
	DDSWrite(0x22, amplitude % 256);

}
