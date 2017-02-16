#include "song_i2cinit.h"
#include"song_IO.h"
void SIICInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_8);
}

u16 RD_ADS(void)
{
	u16 W_B1byte_high, W_B1byte_low, W_B1_word;
	SIICStart();
	SIICWrite(0x91);
	W_B1byte_high = SIICRead(1);
	W_B1byte_low = SIICRead(1);
	W_B1_word = SIICRead(0);
	SIICStop();
	W_B1_word = (W_B1byte_high << 8) + W_B1byte_low;
	return W_B1_word;
}



void ADS1110Config()
{
	SIICStart();
	SIICWrite(0x90);
	SIICWaitAck();
	SIICWrite(0x8c);
	SIICWaitAck();
	SIICStop();
	SDelayUs(10);
}


void SIICStart()
{
	SDA_OUT();
	IIC_SDA = 1;
	IIC_SCL = 1;
	SDelayUs(4);
	IIC_SDA = 0;
	SDelayUs(4);
	IIC_SCL = 0;
}

void SIICStop()
{
	SDA_OUT();
	IIC_SCL = 0;
	IIC_SDA = 0;
	SDelayUs(4);
	IIC_SCL = 1;
	SDelayUs(4);
	IIC_SDA = 1;
	SDelayUs(4);

}

void SIICAck()
{
	SDA_OUT();
	IIC_SCL = 0;
	SDelayUs(2);
	IIC_SDA = 0;
	SDelayUs(2);
	IIC_SCL = 1;
	SDelayUs(2);
	IIC_SCL = 0;
}

u8 SIICWaitAck(void)
{
	u8 ucErrTime = 0;
	SDA_IN();      
	IIC_SDA = 1; SDelayUs(1);
	IIC_SCL = 1; SDelayUs(1);
	while (READ_SDA)
	{
		ucErrTime++;
		if (ucErrTime>250)
		{
			SIICStop();
			return 1;
		}
	}
	IIC_SCL = 0; 
	return 0;
}

void SIICNAck()
{
	SDA_OUT();
	IIC_SCL = 0;
	SDelayUs(2);
	IIC_SDA = 1;
	SDelayUs(2);
	IIC_SCL = 1;
	SDelayUs(2);
	IIC_SCL = 0;
}

void SIICWrite(u8 data)
{
	u8 i;
	SDA_OUT();
	IIC_SCL = 0;
	for (i = 0; i < 8; i++)
	{
		if ((data&0x80) >> 7)
			IIC_SDA = 1;
		else
		{
			IIC_SDA = 0;
		}
		data <<= 1;
		SDelayUs(2);
		IIC_SCL = 1;
		SDelayUs(2);
		IIC_SCL = 0;
		SDelayUs(2);
	}
}

u8 SIICRead(u8 ack)
{
	u8 tmp = 0;
	u8 i;
	SDA_IN();
	for (i = 0; i < 8; i++)
	{
		IIC_SCL = 0;
		SDelayUs(2);
		IIC_SCL = 1;
		tmp <<= 1;
		if (READ_SDA)
			tmp++;
		SDelayUs(2);
	}
	if (ack)
		SIICAck();
	else
	{
		SIICNAck();
	}
	return tmp;


}

void SIIC24WriteB(u16 addr, u8 data)
{

	SIICStart();
	SIICWrite(0XA0 );
	SIICWaitAck();
	SIICWrite(addr);
	SIICWaitAck();
	SIICWrite(data);
	SIICWaitAck();
	SIICStop();
	SDelayMs(10);
}

u8  SIIC24ReadB(u16 addr)
{
	u8 tmp = 0;
	SIICStart();
	SIICWrite(0XA0);
	SIICWaitAck();
	SIICWrite(addr);
	SIICWaitAck();
	SIICStart();
	SIICWrite(0xa1);
	SIICWaitAck();
	tmp = SIICRead(0);
	SIICStop();
	return tmp;

}

u8  SIICCheck()
{
	if (SIIC24ReadB(255) == 0x55)
	{
		return 0;
	}
	else
	{
		SIIC24WriteB(255, 0x55);
		SDelayMs(10);
		if (SIIC24ReadB(255) == 0x55)
			return 0;
	}
	return 1;
}
