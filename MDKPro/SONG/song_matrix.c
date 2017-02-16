#include "song_matrix.h"
GPIO_InitTypeDef keygpio;

void SKeyInit()
{

	GPIO_InitTypeDef Ikeygpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

	Ikeygpio.GPIO_Mode = GPIO_Mode_Out_PP;
	Ikeygpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	Ikeygpio.GPIO_Speed = GPIO_Speed_10MHz;

	keygpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	keygpio.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOC, &Ikeygpio);
	GPIO_Init(GPIOA, &keygpio);

	KEYW = 1;
	KEYR = 1;

}

void SKeyRInit()
{

	keygpio.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_Init(GPIOA, &keygpio);

}

void SKeyWInit()
{
	keygpio.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOA, &keygpio);
}


u16 SKeyScan()
{
	u16 keyV=0;
	SKeyWInit();
	GPIO_Write(GPIOA, (GPIOA->ODR|0x007f)&0xfffe);
	KEYW = 0;
	SDelayMs(1);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	SDelayMs(5);
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:keyV = 41; break;
	case 0x000D:keyV = 31; break;
	case 0x000B:keyV = 21; break;
	case 0x0007:keyV = 11; break;
	}
	KEYR = 1;
	SDelayMs(1);

	SKeyWInit();
	GPIO_Write(GPIOA, (GPIOA->ODR | 0x007f) & 0xfffd);
	//	SDelayMs(10);
	KEYW = 0;
	SDelayMs(1);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	SDelayMs(5);
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:keyV = 42; break;
	case 0x000D:keyV = 32; break;
	case 0x000B:keyV = 22; break;
	case 0x0007:keyV = 12; break;
	}
	KEYR = 1;
	SDelayMs(1);


	SKeyWInit();
	GPIO_Write(GPIOA, (GPIOA->ODR | 0x007f) & 0xfffb);
	//SDelayMs(10);
	KEYW = 0;
	SDelayMs(1);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	SDelayMs(5);
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:keyV = 43; break;
	case 0x000D:keyV = 33; break;
	case 0x000B:keyV = 23; break;
	case 0x0007:keyV = 13; break;
	}
	KEYR = 1;
	SDelayMs(1);


	SKeyWInit();
	GPIO_Write(GPIOA, (GPIOA->ODR | 0x007f) & 0xfff7);
	//	SDelayMs(10);
	KEYW = 0;
	SDelayMs(1);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	SDelayMs(5);
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:keyV = 44; break;
	case 0x000D:keyV = 34; break;
	case 0x000B:keyV = 24; break;
	case 0x0007:keyV = 14; break;
	}
	KEYR = 1;
	SDelayMs(1);


	SKeyWInit();
	GPIO_Write(GPIOA, (GPIOA->ODR | 0x007f) & 0xffef);
	//	SDelayMs(10);
	KEYW = 0;
	SDelayMs(1);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	SDelayMs(5);
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:keyV = 45; break;
	case 0x000D:keyV = 35; break;
	case 0x000B:keyV = 25; break;
	case 0x0007:keyV = 15; break;
	}
	KEYR = 1;
	SDelayMs(1);


	SKeyWInit();
	GPIO_Write(GPIOA, (GPIOA->ODR | 0x007f) & 0xffdf);
	//	SDelayMs(10);
	KEYW = 0;
	SDelayMs(1);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	SDelayMs(5);
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:keyV = 46; break;
	case 0x000D:keyV = 36; break;
	case 0x000B:keyV = 26; break;
	case 0x0007:keyV = 16; break;
	}
	KEYR = 1;
	SDelayMs(1);


	SKeyWInit();
	GPIO_Write(GPIOA, (GPIOA->ODR | 0x007f) & 0xffbf);
	//	SDelayMs(10);
	KEYW = 0;
	SDelayMs(1);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	SDelayMs(5);
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:keyV = 47; break;
	case 0x000D:keyV = 37; break;
	case 0x000B:keyV = 27; break;
	case 0x0007:keyV = 17; break;
	}
	KEYR = 1;
	SDelayMs(1);

	return keyV;
}
	/*
	SKeyWInit();
	GPIO_Write(GPIOA,  0xfffe);
	//SDelayMs(10);
	KEYW = 0;
	SDelayMs(5);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:a = 41; break;
	case 0x000D:a = 31; break;
	case 0x000B:a = 21; break;
	case 0x0007:a = 11; break;
	}
	KEYR = 1;
	SDelayMs(20);

	SKeyWInit();
	GPIO_Write(GPIOA, 0xfffd);
	//	SDelayMs(10);
	KEYW = 0;
	SDelayMs(5);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:a = 42; break;
	case 0x000D:a = 32; break;
	case 0x000B:a = 22; break;
	case 0x0007:a = 12; break;
	}
	KEYR = 1;
	SDelayMs(20);


	SKeyWInit();
	GPIO_Write(GPIOA,  0xfffb);
	//SDelayMs(10);
	KEYW = 0;
	SDelayMs(5);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:a = 43; break;
	case 0x000D:a = 33; break;
	case 0x000B:a = 23; break;
	case 0x0007:a = 13; break;
	}
	KEYR = 1;
	SDelayMs(20);


	SKeyWInit();
	GPIO_Write(GPIOA, 0xfff7);
	//	SDelayMs(10);
	KEYW = 0;
	SDelayMs(5);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:a = 44; break;
	case 0x000D:a = 34; break;
	case 0x000B:a = 24; break;
	case 0x0007:a = 14; break;
	}
	KEYR = 1;
	SDelayMs(20);


	SKeyWInit();
	GPIO_Write(GPIOA,  0xffef);
	//	SDelayMs(10);
	KEYW = 0;
	SDelayMs(5);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:a = 45; break;
	case 0x000D:a = 35; break;
	case 0x000B:a = 25; break;
	case 0x0007:a = 15; break;
	}
	KEYR = 1;
	SDelayMs(20);


	SKeyWInit();
	GPIO_Write(GPIOA, 0xffdf);
	//	SDelayMs(10);
	KEYW = 0;
	SDelayMs(5);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:a = 46; break;
	case 0x000D:a = 36; break;
	case 0x000B:a = 26; break;
	case 0x0007:a = 16; break;
	}
	KEYR = 1;
	SDelayMs(20);


	SKeyWInit();
	GPIO_Write(GPIOA, 0xffbf);
	//	SDelayMs(10);
	KEYW = 0;
	SDelayMs(5);
	KEYW = 1;
	SKeyRInit();
	KEYR = 0;
	switch (GPIOA->IDR & 0x000f)
	{
	case 0x000E:a = 47; break;
	case 0x000D:a = 37; break;
	case 0x000B:a = 27; break;
	case 0x0007:a = 17; break;
	}
	KEYR = 1;
	SDelayMs(20);


	return a;
	*/

void test()
{
	GPIO_InitTypeDef keygpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	keygpio.GPIO_Mode = GPIO_Mode_IPD;
	keygpio.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	keygpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &keygpio);

	keygpio.GPIO_Mode = GPIO_Mode_Out_PP;
	keygpio.GPIO_Speed = GPIO_Speed_50MHz;
	keygpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOA, &keygpio);
}