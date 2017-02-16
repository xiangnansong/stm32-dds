#ifndef SONG_MATRIX
#define SONG_MATRIX

#include "song_IO.h"

#define KEYR  PCout(1)
#define KEYW PCout(0)


void SKeyInit();
u16 SKeyScan();
void SKeyRInit();
void SKeyWInit();

void test();

#endif
