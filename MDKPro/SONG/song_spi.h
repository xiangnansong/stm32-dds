#ifndef SONG_SPI
#define SONG_SPI
#include "song_IO.h"

#define ADC  PBout(9)
#define  SDAADC  PBin(6)
#define SADCLK PBout(7)

#define  CLK  PCout(7)
#define  DAC PAout(8)
#define  SDADAC   PCout(9)

u16  SSPIADCRead();
void SSPIInit();
void SSPIDACWrite(u16 com);
#endif
