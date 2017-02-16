#ifndef SONG_DDS
#define SONG_DDS
#include "song_IO.h"


#define DDSWR	 PCout(8)
#define DDSIOUP	 PCout(6)
#define DDSSR		 PCout(5)

#define KEYR  PCout(1)
#define KEYW PCout(0)

void DDSAInit(void);
void DDSIOInit(void);
void DDSWrite(u16 addr, u16 data);
void DDSConfig(void);
void DDSWA(unsigned long amplitude);
void DDSWF(unsigned long frequency);



#endif