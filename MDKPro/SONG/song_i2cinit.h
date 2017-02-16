#ifndef SONG_IIC
#define SONG_IIC

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "song_IO.h"

#define SDA_IN()  {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=8<<20;}
#define SDA_OUT() {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=3<<20;}


#define IIC_SCL    PBout(8) //SCL
#define IIC_SDA    PBout(5) //SDA	 
#define READ_SDA   PBin(5)  

void ADS1110Config();

u16 RD_ADS(void);
void SIICInit();
void SIICStart();
void SIICStop();
void SIICAck();
void SIICNAck();
void SIICWrite(u8 data);
u8 SIICRead(u8 ack);
void SIIC24WriteB(u16 addr, u8 data);
u8    SIIC24ReadB(u16 addr);
u8 SIICWaitAck(void);
u8  SIICCheck();
#endif
