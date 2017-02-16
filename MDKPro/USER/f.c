#include "song_IO.h"
#include "song_NVIC.h"
#include "song_user_lcd.h"
#include "song_touch.h"
#include "song_gpio_spi.h"
#include "song_matrix.h"
#include "song_spi.h"
#include "song_dds.h"
#include "song_i2cinit.h"
u8 touch = 0;
u8 aorf = 0;
u8 a = 0;
void  get1();
void aorff();
int maintest()
{

	u8 unit=0;
	u8 uord=0;
	u8 tmp=0;
	u32 frequency = 0x00;
	u32 amplitude = 0x00;
	SystemInit();
	SDelayInit(72);
	DDSConfig();

	DDSWrite(0x21, 0x00);
	DDSWrite(0x22, 0xff);

	DDSWrite(0x04, 0x00);
	DDSWrite(0x05, 0x0f);
	DDSWrite(0x06, 0xff);
	DDSWrite(0x07, 0xff);
	DDSWrite(0x08, 0xff);
	DDSWrite(0x09, 0xff);

	while (1)
	{
		aorff();
		if (aorf == 1)
		{
			if (touch == 1)
			{
				frequency = frequency * 10 + a;
				DDSWF(frequency);
			}
		}
		if (aorf == 2)
		{
			if (touch == 1)
			{
				amplitude = amplitude * 10 + a;
				DDSWA(amplitude);
			}
		}
	}
}

void  get1()
{
	touch = 1;
	switch (SKeyScan())
	{
	case 0x21: a = 1; break;
	case 0x22: a = 2; break;
	case 0x23: a = 3; break;
	case 0x31: a = 4; break;
	case 0x32: a = 5; break;
	case 0x33: a = 6; break;
	case 0x41: a = 7; break;
	case 0x42: a = 8; break;
	case 0x43: a = 9; break;
	case 0x12: a = 0; break;
	default:touch = 0; break;
	}
	/*
	if (SKeyScan() == 0x31)
	{
	a = 1;
	touch = 1;
	}
	else if (SKeyScan() == 0x32)
	{
	a = 2;
	touch = 1;
	}

	else if (SKeyScan() == 0x33)
	{
	a = 3;
	touch = 1;
	}

	else if (SKeyScan() == 0x21)
	{
	a = 4;
	touch = 1;
	}

	else if (SKeyScan() == 0x22)
	{
	a = 5;
	touch = 1;
	}

	else if (SKeyScan() == 0x23)
	{
	a = 6;
	touch = 1;
	}

	else if (SKeyScan() == 0x11)
	{
	a = 7;
	touch = 1;
	}

	else if (SKeyScan() == 0x12)
	{
	a = 8;
	touch = 1;
	}

	else if (SKeyScan() == 0x13)
	{
	a = 9;
	touch = 1;
	}

	else if (SKeyScan() == 0x42)
	{
	touch = 1;
	a = 0;
	}

	else touch = 0;
	*/
}

void  aorff()
{

		if (SKeyScan() == 14)
		{
			aorf = 1;
			touch = 1;
		}
		else  if (SKeyScan() == 24)
		{
			aorf = 2;
			touch = 1;
		}
		else
			touch = 0;
	
}


/*


/*#include "song_IO.h"
#include "song_NVIC.h"
#include "song_user_lcd.h"
#include "song_matrix.h"
#include "song_spi.h"
#include "song_dds.h"
#include "song_i2cinit.h"
#include "song_timer.h"
int main()
{
u16 a;
u16 tmp = 0;
u16 b = 0;
u32 ap=0x57c;
u32 ap2 = 0x530;
SystemInit();
SDelayInit(72);
SIICInit();
ADS1110Config();
SSPIInit();
SKeyInit();
STime_Init(9,7199);
LCD_Config();
Lcd_GramScan(2);
LCD_Clear(0, 0, 320, 240, 0x0000);
NVIC_Configuration();
/*while (1)
{
//SKeyScan();
LCD_DisNum(157, 30, SKeyScan(), 0xffff);
}*/
/*	while (SIICCheck())
{
LCD_DispStr(30, 0, "Fail", 0xffff);
}
/*while (1)
{
SSPIDACWrite(0xC000);
SDelayUs(10);
SSPIDACWrite(0xCFFF);
SDelayUs(10);
}*/
/*	for (a = 0; a < 48; a++)
{
LCD_SetPoint(160, a * 5, 0xffff);
}
for (b = 0; b < 64; b++)
{
LCD_SetPoint(b * 5, 120, 0xffff);
}
for (a = 0; a < 9; a++)
{
if (a != 4)
{
LCD_SetPoint(161, (4 + 5 * a) * 5, 0xffff);
}
}

for (a = 0; a < 9; a++)
{
if (a != 4)
{
LCD_SetPoint(162, (4 + 5 * a) * 5, 0xffff);
}
}

for (b = 0; b < 13; b++)
{
if (b != 6)
{
LCD_SetPoint((2 + 5 * b) * 5, 119, 0xffff);
}
}
for (b = 0; b < 13; b++)
{
if (b != 6)
{
LCD_SetPoint((2 + 5 * b) * 5, 118, 0xffff);
}
}

for (b = 0; b < 6; b++)
{

LCD_DisNum(25 * b+8, 121, (6-b),0xffff);

}

for (b = 0; b < 6; b++)
{

LCD_DisNum(25 * (b+7) + 8, 121, b+1, 0xffff);

}

for (a = 0; a < 4; a++)
{
LCD_DisNum(160 - 12, (4 + 5 * a) * 5-5, 4 - a, 0xffff);
}


for (a = 0; a < 4; a++)
{
LCD_DisNum(160 - 17, (4 + 5 * (a+5)) * 5-5, -(a+1), 0xffff);
}
*/
//LCD_DrawCoords();
/*while (1)
{

for (a = 0; a < 160; a++)
{

tmp = 360 - (SSPIADCRead() * 240) / 4095;
SDelayMs(50);
LCD_DrawLine(a * 2, trans(tmp, (a + 1) * 2), 360 - (SSPIADCRead() * 240) / 4095, 0xffff);
LCD_DrawLine(a * 2, 0, (a + 1) * 2,0, 0xffff);

}
LCD_Clear(0, 0, 320, 240, 0x0000);

}*/
/*	while (1)
{

LCD_DrawCoords();
tmp = 0;
for (a = 0; a < 320; a++)
{
LCD_SetPoint(a, trans(RD_ADS() * 119 / 65535), 0xffff);
SDelayMs(10);
}

LCD_Clear(0, 0, 320, 240, 0x0000);
}
*/
//////*****************DDS model**********///////////////
/*	DDSConfig();

DDSWrite(0x1d, 0x00);
DDSWrite(0x1e, 0x47);
DDSWrite(0x1F, 0x01);
DDSWrite(0x20, 0x20);

DDSWrite(0x21, 0x00);
DDSWrite(0x22, 0xff);
DDSWrite(0x01, 0xff);
DDSWrite(0x03, 0xff);

DDSWrite(0x04, 0x00);
DDSWrite(0x05, 0x0f);
DDSWrite(0x06, 0xff);
DDSWrite(0x07, 0xff);
DDSWrite(0x08, 0xff);
DDSWrite(0x09, 0xff);
while (1)
{
DDSWF(ap);
DDSWA(ap2);
}

//********************************
/*while (1)
{
LCD_DisNum(157, 30, SKeyScan(), 0xffff);
}*/

/*	GPIO_InitTypeDef gpioa;
SystemInit();
SDelayInit(72);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
gpioa.GPIO_Mode = GPIO_Mode_Out_PP;
gpioa.GPIO_Pin = GPIO_Pin_0;
gpioa.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &gpioa);
PAout(0) = 0;
SDelayMs(100);
PAout(0) = 1;
SDelayMs(100);
PAout(0) = 0;
}

#include "song_IO.h"
#include "song_NVIC.h"
#include "song_user_lcd.h"
#include "song_touch.h"
#include "song_gpio_spi.h"
#include "song_matrix.h"
#include "song_spi.h"
#include "song_dds.h"
#include "song_i2cinit.h"
u8 touch = 0;
u8 aorf = 0;
u8 a = 0;
void  get1();
void aorff();
int main()
{

	u8 unit = 0;
	u8 uord = 0;
	u8 tmp = 0;
	u32 frequency = 0x00;
	u32 amplitude = 0x00;
	SystemInit();
	STime_Init(99, 7199);
	SDelayInit(72);
	DDSConfig();
	SKeyInit();

	DDSWrite(0x21, 0x00);
	DDSWrite(0x22, 0xff);

	DDSWrite(0x04, 0x00);
	DDSWrite(0x05, 0x0f);
	DDSWrite(0x06, 0xff);
	DDSWrite(0x07, 0xff);
	DDSWrite(0x08, 0xff);
	DDSWrite(0x09, 0xff);

	while (1)
	{
		aorff();
		if (aorf == 1)
		{
			if (touch == 1)
			{
				frequency = frequency * 10 + a;
				DDSWF(frequency);
			}
		}
		if (aorf == 2)
		{
			if (touch == 1)
			{
				amplitude = amplitude * 10 + a;
				DDSWA(amplitude);
			}
		}
	}

}

void  get1()
{
	touch = 1;
	switch (SKeyScan())
	{
	case 0x21: a = 1; break;
	case 0x22: a = 2; break;
	case 0x23: a = 3; break;
	case 0x31: a = 4; break;
	case 0x32: a = 5; break;
	case 0x33: a = 6; break;
	case 0x41: a = 7; break;
	case 0x42: a = 8; break;
	case 0x43: a = 9; break;
	case 0x12: a = 0; break;
	default:touch = 0; break;
	}
	/*
	if (SKeyScan() == 0x31)
	{
	a = 1;
	touch = 1;
	}
	else if (SKeyScan() == 0x32)
	{
	a = 2;
	touch = 1;
	}

	else if (SKeyScan() == 0x33)
	{
	a = 3;
	touch = 1;
	}

	else if (SKeyScan() == 0x21)
	{
	a = 4;
	touch = 1;
	}

	else if (SKeyScan() == 0x22)
	{
	a = 5;
	touch = 1;
	}

	else if (SKeyScan() == 0x23)
	{
	a = 6;
	touch = 1;
	}

	else if (SKeyScan() == 0x11)
	{
	a = 7;
	touch = 1;
	}

	else if (SKeyScan() == 0x12)
	{
	a = 8;
	touch = 1;
	}

	else if (SKeyScan() == 0x13)
	{
	a = 9;
	touch = 1;
	}

	else if (SKeyScan() == 0x42)
	{
	touch = 1;
	a = 0;
	}

	else touch = 0;
	
}

void  aorff()
{

	if (SKeyScan() == 14)
	{
		aorf = 1;
		touch = 1;
	}
	else  if (SKeyScan() == 24)
	{
		aorf = 2;
		touch = 1;
	}
	else
		touch = 0;
}

void TIM3_IRQHandler()
{
	if (TIM_GetFlagStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		get1();
	}
}


*/


















/*

#include "song_IO.h"
#include "song_NVIC.h"
#include "song_user_lcd.h"
#include "song_touch.h"
#include "song_gpio_spi.h"
#include "song_matrix.h"
#include "song_spi.h"
#include "song_dds.h"
#include "song_i2cinit.h"
#include "song_timer.h"
u8 touch = 0;
u8 aorf = 0;
u8 a = 0;
void  get1();
void aorff();
int main()
{
u8 unit = 0;
u8 uord = 0;
u8 tmp = 0;
u32 ap = 0x00;
u32 ap1 = 0x00;
SystemInit();
SDelayInit(72);

STime_Init(99, 7199);

SKeyInit();
DDSConfig();
DDSIOInit();
DDSWrite(0x21, 0x00);
DDSIOInit();
DDSWrite(0x22, 0xff);
DDSIOInit();
DDSWrite(0x04, 0x00);
DDSIOInit();
DDSWrite(0x05, 0x00);
DDSIOInit();
DDSWrite(0x06, 0xff);
DDSIOInit();
DDSWrite(0x07, 0xff);
DDSIOInit();
DDSWrite(0x08, 0xff);
DDSIOInit();
DDSWrite(0x09, 0xff);

while (1)
{
aorff();
if (aorf == 1)
{
if (touch == 1)
{
ap = ap * 10 + a;
DDSIOInit();
DDSWF(ap);
}
}
if (aorf == 2)
{
if (touch == 1)
{
ap1 = ap1 * 10 + a;
DDSIOInit();
DDSWA(ap1);
}
}
}

}


void  get1()
{
touch = 1;
switch (SKeyScan())
{
case 0x21: a = 1; break;
case 0x22: a = 2; break;
case 0x23: a = 3; break;
case 0x31: a = 4; break;
case 0x32: a = 5; break;
case 0x33: a = 6; break;
case 0x41: a = 7; break;
case 0x42: a = 8; break;
case 0x43: a = 9; break;
case 0x12: a = 0; break;
default:touch = 0; break;
}
}

void  aorff()
{

if (SKeyScan() == 14)
{
aorf = 1;
touch = 1;
}
else  if (SKeyScan() == 24)
{
aorf = 2;
touch = 1;
}
else
touch = 0;
}


void TIM3_IRQHandler()
{
if (TIM_GetFlagStatus(TIM3, TIM_IT_Update) != RESET)
{
TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
get1();
}
}

*/