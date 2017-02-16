#ifndef SONG_HC05
#define SONG_HC05
#include "song_IO.h"
#include "song_usart.h"

#define AT PDout(2)
#define OK PDin(3)

void SHc05IO();

#endif