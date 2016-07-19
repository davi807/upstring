#ifndef UTF8_H
#define UTF8_H

#include <stdlib.h>

unsigned int ord(char *,unsigned char *);
void chr(unsigned int ,char *, unsigned char *);
char *upChr(unsigned int code, unsigned char *count);
#endif
