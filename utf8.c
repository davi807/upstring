#include "utf8.h"
unsigned int ord(char *stream,unsigned char *count){
    unsigned int i,ord;
    unsigned char u,c = stream[0];
    char *p = 0;
    *count = 1;
    if(c<128){
        return c;
    }
    else if(c>192 && c<224)
        u = 2;
    else if(c>224 && c<240)
        u = 3;
    else if(c>240 && c<248)
        u = 4;
    else if(c>248 && c<252)
        u = 5;
    else if(c>252 && c<254)
        u = 6;
    else return 0;

    ++u;
    ord = ( (unsigned char)(c<<u))>>u;
    u-=2;
    p = stream+1;
    for(i=0;i<u;++i){
        c = p[i];
        ord = ord<<6;
        ord = ord | (c ^ 0x80);
    }
    *count = u+1;
    return ord;
}

void chr(unsigned int code, char *chr, unsigned char *count){
	unsigned char c=0;
	char bit=0, byte=1;
	unsigned int cpcode = code;
	*count = 0;

	while(cpcode){
		cpcode = cpcode>>1;
		++bit;
	}
	if(bit<=7){
		chr[0] = (char)code;
	}else if(bit>7){
		byte = (bit/6)+1;
		cpcode = code;
		for(bit=byte-1;bit>0;--bit){
			c = cpcode; cpcode=cpcode>>6;
			c=(c<<2); c=c>>2;
			c = c | 0x80;
			chr[(short)bit] = c;
		}
		bit=byte;
		c=0;
		while(bit--)
			c = (c<<1)^1;
		while(c<128){
			c = c<<1;
		}
		chr[0] = c | cpcode;
	}
	*count = byte;
}


char *upChr(unsigned int code, unsigned char *count){
    char *res,*ch = (char*)malloc(6);
    chr(code,ch,count);
    res = realloc(ch,*count);
    return res;
}
