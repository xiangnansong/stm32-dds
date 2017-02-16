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
#include "atk_ncr.h"
atk_ncr_point READ_BUF[200];
int main()
{

	u16 i = 0;
	u8 temp = 0;
	u8 tcnt = 0;
	u8 res[10];
	u8 key;
	u16 pcnt = 0;
	u8 mode = 1;
	u8 tmp;
	u32 range = 0;
	u32 frequency = 0;
	u16 x = 0;
	u16 y = 0;
	u16 tx = 0;
	u16 ty = 0;
	u8 deltaF = 0;
	u8 deltaA = 0;
	u8 aorf = 1;
	SystemInit();
	SDelayInit(72);
	LCD_Config();
	Touch_Init();
	Lcd_GramScan(2);
	LCD_Clear(0, 0, 320, 240, 0xffff);
	alientek_ncr_init();
	NVIC_Configuration();
	DDSConfig();
	/*	while (Touch_Calibrate())
		{
		};
		LCD_Clear(0, 0, 320, 240, 0x0000);
		while (1)
		{
		/*if (touch_flag == 1)
		{

		if (Get_touch_point(&display, Read_2046_2(), &touch_para) != DISABLE)
		{
		LCD_SetPoint(display.x, display.y, 0xffff);
		}
		}*/
	//LCD_DisNum(0, 0, 300, 0x0000);
	/*while (Touch_Calibrate())
	{
	};
	LCD_Clear(0, 0, 320, 240, 0xffff);
	DDSUI(0);
	while (1)
	{
		if (touch_flag == 1)
		{

			if (Get_touch_point(&display, Read_2046(), &touch_para) != DISABLE)
			{
				x = display.x;
				y = display.y;
				if (y > 200)
				{
					if (x < 40)
					{
						while (touch_flag)
						{
							Read_2046_2();
						};
						if (aorf == 1)
						{
							frequency += 1000;
						}
						else if (aorf == 2)
						{
							range += 1000;
						}

					}
					else if (x > 50 && x < 90)
					{
						while (touch_flag)
						{
							Read_2046_2();
						};
						if (aorf == 1)
						{
							frequency += 100;
						}
						else if (aorf == 2)
						{
							range += 100;
						}
					}
					else if (x > 100 && x < 140)
					{
						while (touch_flag)
						{
							Read_2046_2();
						};
						if (aorf == 1)
						{
							frequency += 10;
						}
						else if (aorf == 2)
						{
							range += 10;
						}
					}
					else if (x > 180 && x < 220)
					{
						while (touch_flag)
						{
							Read_2046_2();
						};
						if (aorf == 1)
						{
							frequency -= 10;
						}
						else if (aorf == 2)
						{
							range -= 10;
						}
					}
					else if (x > 230 && x < 270)
					{
						while (touch_flag)
						{
							Read_2046_2();
						};
						if (aorf == 1)
						{
							frequency -= 100;
						}
						else if (aorf == 2)
						{
							range -= 100;
						}
					}
					else if (x > 280)
					{
						while (touch_flag)
						{
							Read_2046_2();
						};
						if (aorf == 1)
						{
							frequency -= 1000;
						}
						else if (aorf == 2)
						{
							range -= 1000;
						}
					}
				}
				else if (y > 130 && y < 190)
				{
					if (x>50 && x < 110)
					{
						aorf = 1;
					}
					else if (x>210 && x < 270)
					{
						aorf = 2;
					}
				}
				else if (x>250 && x<300)
				{
					if (y>10 && y < 60)
					{
						if (aorf == 1)
						{
							frequency = 0;
						}
						else if (aorf == 2)
						{
							range = 0;
						}
					}
				}

				else if (y>10 && y < 40)
				{
					if (x>10 && x < 40)
					{
						for (i = 0; i<320; i++)
						{
							DDSUI(i);
							LCD_Clear(320 - i, 0, i, 240, 0xffff);
							SDelayMs(1);
						}
					}
				}

				if (y > 70 && y < 190)
				{
					if (x>120 && x < 200)
					{
						while (1)
						{
							SDelayMs(1);
							if (touch_flag == 1 && Get_touch_point(&display, Read_2046_2(), &touch_para) != DISABLE)
							{
								tcnt = 0;
								tx = display.x;
								ty = display.y;
								if (ty > 70 && ty < 190)
								{
									if (tx>120 && tx < 200)
									{
										LCD_SetPoint(tx, ty, 0x0000);
									}
								}
								if (pcnt < 200)
								{
									if (pcnt)
									{
										if ((READ_BUF[pcnt - 1].y != ty) && (READ_BUF[pcnt - 1].x != tx))
										{
											READ_BUF[pcnt].x = tx;
											READ_BUF[pcnt].y = ty;
											pcnt++;
										}
									}
									else
									{
										READ_BUF[pcnt].x = tx;
										READ_BUF[pcnt].y = ty;
										pcnt++;
									}
								}
							}
							else
							{
								tcnt++;
								SDelayMs(10);
								i++;
								if (tcnt == 40)
								{
									if (pcnt)
									{
										alientek_ncr(READ_BUF, pcnt, 1, mode, (char*)res);
										pcnt = 0;
										temp = (*res) - 48;
									}
									LCD_Clear(120, 70, 80, 120, 0xffff);
									tcnt = 0;
									if (aorf == 1)
									{
										frequency = frequency * 10 + temp;
									}
									else if (aorf == 2)
									{
										range = range * 10 + temp;
									}
									break;
								}
							}
						}
					}
				}
				x = 0;
				y = 0;
			}
		}
		DDSWA(range);
		DDSWF(frequency);
		LCD_DispStr(120, 30, "range:", 0x0000);
		LCD_DisNum(180, 30, range, 0x0000);
		LCD_DispStr(120, 50, "frequency:", 0x0000);
		LCD_DisNum(180, 50, frequency, 0x0000);
		LCD_DispStr(50, 30, "mode:", 0x0000);
		if (range == 0)
		{
			LCD_DispStr(186, 30, "          ", 0x0000);
			LCD_DisNum(180, 30, range, 0x0000);
		}
		if (frequency == 0)
		{
			LCD_DispStr(186, 50, "          ", 0x0000);                                        
			LCD_DisNum(180, 50, frequency, 0x0000);
		}


		if (aorf == 1)
		{
			LCD_DispChar(80, 30, 'F', 0x0000);
		}
		else if (aorf == 2)
		{
			LCD_DispChar(80, 30, 'A', 0x0000);
		}
	}
}

*/

/*#include "song_IO.h"
#include "lcd.h"
int main()
{
	SystemInit();
	SDelayInit(72);
	LCD_Init();
	POINT_COLOR = RED;
	while (1)
	{
		POINT_COLOR = RED;
		LCD_ShowString(30, 50, 200, 16, 16, "WarShip STM32 ^_^");
	}
}*/

//以下是键盘控制的//
/*
#include "song_IO.h"
#include "song_matrix.h"
#include "song_user_lcd.h"
#include "song_dds.h"
int main()
{
	u32 frequency = 0;
	u32 amplitude = 0;
	u16 keyValue = 0;
	u16 tmp;
	u8 fval[6] = { 0 };
	u8 aval[6] = { 0 };
	u8 position = 0;
	u8 preposition = 0;
	u8 mode = 1;
	u8 i = 0;
	SystemInit();
	SDelayInit(72);

	LCD_Config();
	Lcd_GramScan(2);
	LCD_Clear(0, 0, 320, 240, 0xffff);
	SKeyInit();
	DDSConfig();
	while (1)
	{
		if (SKeyScan() != 0)
		{
			keyValue = SKeyScan();
			SDelayMs(10);
			if (SKeyScan() != 0)
			{

				if (keyValue == 11)
				{
					mode = 1;
				}
				else if (keyValue == 13)
				{
					mode = 2;
				}
				else if (keyValue == 21)
				{
					preposition = position;
					position += 1;
					if (position > 5)
					{
						position = 5;
					}
				}
				else if (keyValue == 23)
				{
					preposition = position;
					if (position < 1)
					{
						position = 0;
					}
					else
					{
						position -= 1;
					}
				}
				else if (keyValue == 12)
				{
					if (mode == 1)
					{
						if (position >= 0 && position<6)
						{
							if (fval[position] < 10 && fval[position]>0)
								fval[position]--;
							else fval[position] = 0;
						}
					}
					else if (mode == 2)
					{
						if (position >= 0 && position < 6)
						{
							if (aval[position] < 10 && aval[position]>0)
								aval[position]--;
							else aval[position] = 0;
						}
					}
				}
				else if (keyValue == 32)
				{
					if (mode == 1)
					{
						if (position >= 0 && position < 6)
						{
							if (fval[position] < 9)
							{
								fval[position]++;
							}
							else fval[position] = 0;
						}

					}
					else if (mode == 2)
					{
						if (position >= 0 && position < 6)
						{
							if (aval[position] < 9)
							{
								aval[position]++;
							}
							else aval[position] = 0;
						}
					}
				}
			}
		}
		frequency = fval[0] + fval[1] * 10 + fval[2] * 100 + fval[3] * 1000 + fval[4] * 10000 + fval[5] * 100000;
		amplitude = aval[0] + aval[1] * 10 +aval[2] * 100 + aval[3] * 1000 + aval[4] * 10000 + aval[5] * 100000;
		LCD_DispStr(120, 30, "MODE: ", 0x0000);
		if (mode == 1)
		{
			LCD_DispStr(150, 30, "FREQUENCY", 0x0000);
		}
		else if (mode == 2)
		{
			LCD_DispStr(150, 30, "AMPLITUDE", 0X0000);
		}
		LCD_DispStr(100, 60, "FREQUENCY: ", 0x0000);
		LCD_DispStr(100, 90, "AMPLITUDE: ", 0x0000);
		for (i = 0; i < 6; i++)
		{
			LCD_DisNum(180 + i * 6, 60, fval[5 - i], 0x0000);
		}
		for (i = 0; i < 6; i++)
		{
			LCD_DisNum(180 + i * 6, 90, aval[5 - i], 0x0000);
		}
		if (mode == 1)
		{
			LCD_DispChar(180 + 6 * (5 - position), 90 + 12, ' ', 0x0000);
			if (preposition != position)
			{

				LCD_DispChar(180 + 6 * (5 - preposition), 60 + 12, ' ', 0x0000);
				LCD_DispChar(180 + 6 * (5 - position), 60 + 12, '^', 0x0000);
			}
			else
				LCD_DispChar(180 + 6 * (5 - position), 60 + 12, '^', 0x0000);
		}
		else if (mode == 2)
		{
			LCD_DispChar(180 + 6 * (5 - position), 60 + 12, ' ', 0x0000);
			if (preposition != position)
			{

				LCD_DispChar(180 + 6 * (5 - preposition), 90 + 12, ' ', 0x0000);
				LCD_DispChar(180 + 6 * (5 - position), 90 + 12, '^', 0x0000);
			}
			else 
				LCD_DispChar(180 + 6 * (5 - position), 90 + 12, '^', 0x0000);
		}
		LCD_DispStr(180 + 6 * 6, 60, "Khz", 0x0000);
		LCD_DispStr(180 + 6 * 6, 90, "Mv", 0x0000);
		DDSIOInit();
		DDSWA(amplitude);
		DDSWF(frequency);
	}
}

*/

#include "song_IO.h"
#include "song_user_lcd.h"
#include "song_touch.h"
#include "song_dds.h"
#include "song_NVIC.h"

#include "atk_ncr.h"
atk_ncr_point READ_BUF[200];
unsigned char bnum[10][64] = {
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x0F, 0xF0,
	0x1C, 0x38, 0x38, 0x38, 0x38, 0x1C, 0x30, 0x1C, 0x70, 0x0C, 0x70, 0x0C, 0x70, 0x0C, 0x70, 0x0C,
	0x70, 0x0C, 0x70, 0x0C, 0x70, 0x0C, 0x70, 0x0C, 0x70, 0x0C, 0x30, 0x1C, 0x38, 0x1C, 0x38, 0x18,
	0x1C, 0x38, 0x1F, 0xF0, 0x07, 0xE0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x01, 0xC0,
		0x03, 0xC0, 0x07, 0xC0, 0x1D, 0xC0, 0x19, 0xC0, 0x11, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0,
		0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0,
		0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x1F, 0xF8,
		0x3C, 0x38, 0x38, 0x1C, 0x70, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x18, 0x00, 0x38, 0x00, 0x38,
		0x00, 0x70, 0x00, 0xE0, 0x00, 0xC0, 0x01, 0xC0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00, 0x1C, 0x00,
		0x3C, 0x00, 0x3F, 0xFC, 0x3F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x0F, 0xF8,
		0x1C, 0x38, 0x38, 0x1C, 0x30, 0x1C, 0x10, 0x1C, 0x00, 0x1C, 0x00, 0x18, 0x00, 0x78, 0x03, 0xE0,
		0x03, 0xF0, 0x00, 0x78, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x10, 0x0C, 0x70, 0x1C, 0x38, 0x1C,
		0x3C, 0x38, 0x1F, 0xF8, 0x0F, 0xE0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x70,
		0x00, 0x70, 0x00, 0xF0, 0x01, 0xF0, 0x01, 0xB0, 0x03, 0xB0, 0x07, 0x30, 0x0E, 0x30, 0x0C, 0x30,
		0x1C, 0x30, 0x38, 0x30, 0x30, 0x30, 0x70, 0x30, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0x00, 0x30,
		0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x1F, 0xF8,
		0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x38, 0x00, 0x30, 0x00, 0x37, 0xC0, 0x3F, 0xF0, 0x78, 0x78,
		0x70, 0x38, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x0C, 0x00, 0x0C, 0x20, 0x1C, 0x60, 0x1C, 0x70, 0x1C,
		0x70, 0x78, 0x3F, 0xF0, 0x1F, 0xE0, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0xE0,
		0x01, 0xC0, 0x03, 0x80, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x1F, 0xF0, 0x1F, 0xF8,
		0x3C, 0x1C, 0x38, 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x70, 0x0E, 0x38, 0x0E,
		0x3C, 0x1C, 0x1F, 0xF8, 0x0F, 0xF0, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFE, 0x7F, 0xFE,
		0x00, 0x0E, 0x00, 0x1C, 0x00, 0x18, 0x00, 0x38, 0x00, 0x30, 0x00, 0x70, 0x00, 0x60, 0x00, 0xE0,
		0x00, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x00, 0x07, 0x00,
		0x07, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x1F, 0xF0,
		0x38, 0x38, 0x30, 0x1C, 0x30, 0x1C, 0x30, 0x1C, 0x30, 0x1C, 0x38, 0x38, 0x3C, 0x78, 0x0F, 0xE0,
		0x1F, 0xF0, 0x3C, 0x78, 0x78, 0x1C, 0x70, 0x1C, 0x60, 0x0C, 0x60, 0x0C, 0x70, 0x0C, 0x70, 0x1C,
		0x78, 0x3C, 0x3F, 0xF8, 0x1F, 0xF0, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	},
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x1F, 0xF0,
		0x3C, 0x78, 0x70, 0x3C, 0x70, 0x1C, 0x60, 0x1C, 0x60, 0x1C, 0x60, 0x1C, 0x60, 0x1C, 0x70, 0x38,
		0x78, 0x78, 0x3F, 0xF8, 0x1F, 0xF0, 0x00, 0xE0, 0x00, 0xE0, 0x01, 0xC0, 0x01, 0xC0, 0x03, 0x80,
		0x03, 0x80, 0x07, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	},
};
u8 invert = 1;
int main()
{
	u8 i, j, m;
	u8 invflag = 0;
	u16 time=0;
	u32 frequency = 0;
	u32 amplitude = 0;
	u8 res[2] = {0};
	int8_t aval[6] = { 0 };
	int8_t fval[6] = { 0 };
	int8_t  position = 0;
	u8 mode = 2;
	u8 temp = 0;
	u16 x = 0;
	u16 y = 0;
	u8  tcnt = 0;
	u8 pcnt = 0;
	SystemInit();
	SDelayInit(72);
	LCD_Config();
	NVIC_Configuration();
	Lcd_GramScan(2);
	alientek_ncr_init();
	LCD_Clear(0, 0, 320, 240, 0x0000);
	Touch_Init();
	while (Touch_Calibrate())
	{};
	LCD_Clear(0, 0, 320, 240, 0x0000);
	DDSUI2();
	while (1)
	{
		if (touch_flag == 1)
		{
			if (Get_touch_point(&display, Read_2046(), &touch_para) != DISABLE)
			{
				x = display.x;
				y = display.y;
				if (x > 170 & x<312)
				{
					if (y>125 & y < 236)
					{
						while (1)
						{
							if (touch_flag == 1 && Get_touch_point(&display, Read_2046_2(), &touch_para) != DISABLE)
							{
								tcnt = 0;
								x = display.x;
								y = display.y;
								if (x > 170 & x < 312)
								{
									if (y>125 & y < 236)
									{
										LCD_SetPoint(x, y, 0xffff);
									}
								}
								//记录点
								if (pcnt < 200)
								{
									if (pcnt)
									{
										if ((READ_BUF[pcnt - 1].y != y) && (READ_BUF[pcnt - 1].x != x))
										{
											READ_BUF[pcnt].x = x;
											READ_BUF[pcnt].y = y;
											pcnt++;
										}
									}
									else
									{
										READ_BUF[pcnt].x = x;
										READ_BUF[pcnt].y = y;
										pcnt++;
									}
								}
								//停笔400ms以上时，进行识别。
							}
							else
							{
								tcnt++;
								SDelayMs(10);
								i++;
								if (tcnt == 40)
								{
									if (pcnt)
									{
										alientek_ncr(READ_BUF, pcnt, 1, 1, (char*)res);
										pcnt = 0;
										temp = (*res) - 48;
										if (mode == 1)
										{
											fval[position] = temp;
										}
										else 
										{
											aval[position] = temp;
										}
										tcnt = 0;
										LCD_Clear(171, 126, 141, 110, 0x0000);
										break;
									}
								}
							}
						}
					}
				}

				else
				{
					while (touch_flag)
					{
						Read_2046();
					}
					if (x > 94 & x < 126)
					{
						if (y>164 & y < 196)
						{
							position--;
							if (position>5)
								position = 0;
							else if (position < 0)
								position = 5;
						}
					}

					else if (x>30 & x < 62)
					{
						if (y>164 & y < 196)
						{
							position++;
							if (position>5)
								position = 0;
							else if (position < 0)
								position = 5;
						}
					}
					else if (x>62 & x < 94)
					{
						if (y>164 & y < 196)
						{
							if (mode == 1)
							{
								mode = 2;
							}
							else
							{
								mode = 1;
							}
						}
						else 	if (y > 196 & y < 228)
						{
							if (mode == 1)
							{
								fval[position]--;
								if (fval[position] < 0)
									fval[position] = 9;
							}
							else if (mode == 2)
							{
								aval[position]--;
								if (aval[position] < 0)
									aval[position] = 9;
							}
						}
						else 	if (y>132 & y < 164)
						{
							if (mode == 1)
							{
								fval[position]++;
								if (fval[position] > 9)
									fval[position] = 0;
							}
							else if (mode == 2)
							{
								aval[position]++;
								if (aval[position] > 9)
									aval[position] = 0;
							}
						}
					}
				}

			}
		}
		frequency = fval[0] + fval[1] * 10 + fval[2] * 100 + fval[3] * 1000 + fval[4] * 10000 + fval[5] * 100000;
		amplitude = aval[0] + aval[1] * 10 + aval[2] * 100 + aval[3] * 1000 + aval[4] * 10000 + aval[5] * 100000;
		if (invert == 1)
		{
			for (i = 0; i < 6; i++)
			{
				if (i != position)
				{
					LCD_DispAnyChar(130 + 16 * (5 - i), 22, 16, 32, bnum[fval[i]], 0xffff);
					LCD_DispAnyChar(130 + 16 * (5 - i), 70, 16, 32, bnum[aval[i]], 0xffff);
				}
				else if (i == position)
				{
					if (mode == 1)
					{
						LCD_SetBack(0xffff);
						LCD_DispAnyChar(130 + 16 * (5 - i), 22, 16, 32, bnum[fval[i]], 0x0000);
						LCD_SetBack(0x0000);
						LCD_DispAnyChar(130 + 16 * (5 - i), 70, 16, 32, bnum[aval[i]], 0xffff);
					}
					else if (mode == 2)
					{
						LCD_SetBack(0xffff);
						LCD_DispAnyChar(130 + 16 * (5 - i), 70, 16, 32, bnum[aval[i]], 0x0000);
						LCD_SetBack(0x0000);
						LCD_DispAnyChar(130 + 16 * (5 - i), 22, 16, 32, bnum[fval[i]], 0xffff);
					}
				}
			}
		}
		else if (invert == 0)
		{
			for (i = 0; i < 6; i++)
			{
				LCD_DispAnyChar(130 + 16 * (5 - i), 22, 16, 32, bnum[fval[i]], 0xffff);
				LCD_DispAnyChar(130 + 16 * (5 - i), 70, 16, 32, bnum[aval[i]], 0xffff);
			}
		}
		time++;
		SDelayMs(1);
		if (time > 100)
		{
			if (invert == 0)
			{
				invert = 1;
			}
			else
				invert = 0;
			time = 0;
		}
	}
}
/*
#include "song_IO.h"
#include "song_usart.h"
#include "song_user_lcd.h"
#include "song_NVIC.h"
#include "song_hc05.h"
int main()
{
	u8  t;
	u8 len;
	SystemInit();
	SDelayInit(72);
	LCD_Config();
	NVIC_Configuration();
	SUsartInit(9600);
	Lcd_GramScan(2);
	SHc05IO();
	LCD_Clear(0, 0, 320, 240, 0x0000);
	printf("AT+ROLE=0\r\n");
	printf("AT+CMODE=1\r\n");
	printf("AT+UART=9600,0,0\r\n");
	printf("AT+NAME=song\r\n");
	while (1)
	{
		if (USART_RX_STA & 0x8000)
		{
			len = USART_RX_STA & 0x3fff;
			printf("\r\n发送的消息为:\r\n\r\n");//将接受的信息返回发送
			for (t = 0; t<len; t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);
				while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);//wite finish
			}
			printf("\r\n\r\n");
			USART_RX_STA = 0;
		}
	}
}*/
