#define STM32F10X_HD
#ifndef SONG_NVIC_H
#define SONG_NVIC_H
#include "song_IO.h"

void NVIC_Configuration(void);
void SongExitInit(void);
void SongTimeExit(uint16_t period, uint16_t prescaler);
#endif
