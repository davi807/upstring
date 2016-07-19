//UTF8 Pascal like string
#ifndef UPSTRING_H
#define UPSTRING_H

#include <stdio.h>
#include <string.h>
#include "utf8.h"

#ifndef LONG_UNICODE
#define sint short
#else
#define sint int
#endif

#define upNew(a,b) (b*)malloc((a)*sizeof(b))
#define upLoop(a,b,c) for(a=(b);a<(c);++a)
#define nls (upstring){0,0}

typedef struct upstring upstring;
struct upstring{
    unsigned sint *text;
    unsigned int length;
};

//Constructor functions
upstring upString(char *src);
upstring upCopy(upstring src,unsigned int start,unsigned int count);
upstring upClone(upstring );

//Main string functions
unsigned int upLength(upstring);
unsigned int upCount(upstring);
char *upToString(upstring);

//Destructor
void upReset(upstring *);
int _upClean(upstring, char);
void upUnsetSoon(upstring);
int upUnsetAll();

//Temporary strings
upstring tpString(char *src);
upstring tpCopy(upstring src,unsigned int start,unsigned int count);
upstring tpClone(upstring );

/**
String tools
*/
//Compare functuins
char upComp(upstring a, upstring b);
long upPos(upstring search, upstring source);

//Add to string
void upAppend(upstring *source, upstring part);
void upInsert(upstring part, upstring *source, unsigned int start, unsigned int length);

//Remove string part
void upDelete(upstring *source, unsigned int start, unsigned int length);

//I/O
//Write
void upWrite(FILE *,upstring);
void upConsoleWrite(upstring);
void upConsoleWriteln(upstring);

//Read
upstring upReadC(FILE *,char );
upstring upReadN(FILE *,unsigned int );
upstring upRead(FILE *f);
upstring upConsoleRead();
upstring upConsoleReadln();
#endif
