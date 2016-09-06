#include "upstring.h"
//two string compare
char upComp(upstring a, upstring b){
    int i;
    unsigned int j;
    if(upLength(a)!=upLength(b))
        return 0;
    j  = upCount(a);
    if(j!=upCount(b))
        return 0;
    i=memcmp(a.text,b.text,j);
    if(i==0) return 1;
    else return 0;
}
//search substring
long upPos(upstring search, upstring source){
    char f=0;
    unsigned int i,j;
    long end = source.length-search.length+1;
    if(source.length==0 || search.length==0)
        return -1;
    if(end <= 0)
        return -1;
    upLoop(i,0,end){
        if(source.text[i] == search.text[0]){
            if(i+search.length>source.length)
                break;
            upLoop(j,1,search.length)
                if(search.text[j] != source.text[i+j])
                    break;
             if(j==search.length){
                f=1;
                break;
             }
        }
    }
    if(f)
        return i;
    else return -1;
}

//Append string
void upAppend(upstring *source, upstring part){
    unsigned int len;
    unsigned sint *addr=0;

    len = source->length + part.length;
    addr = upNew(len,unsigned sint);
    memcpy( (void*)(addr),source->text,sizeof(sint)*source->length);
    memcpy( (void*)(addr+source->length),part.text,sizeof(sint)*part.length);
    free(source->text);
    source->text = addr;
    source->length = len;
}

//insert part
void upInsert(upstring part, upstring *source, unsigned int start, unsigned int length){
    upstring tmp = nls,t1,t2;

    if(source->length<start)
        return;
    if(part.length<length)
        length = part.length;

    tmp = upCopy(*source,0,start);
    t1 = upCopy(part,0,length);
    upAppend(&tmp,t1); upReset(&t1);
    t2 = upCopy(*source,start,source->length);
    upAppend(&tmp,t2); upReset(&t2);
    free(source->text);
    source->text = tmp.text;
    source->length = tmp.length;
}

//Delete from string
void upDelete(upstring *source, unsigned int start, unsigned int length){
    upstring res=nls,t1,t2;
    if(start > source->length)
        return;
    if(start+length>source->length)
        length = source->length-start;
    t1 = upCopy(*source,0,start);
    t2 = upCopy(*source,start+length,source->length);
    upAppend(&res,t1); upReset(&t1);
    upAppend(&res,t2); upReset(&t2);
    upReset(source);
    *source = res;
}

//I/O

//Write to file
void upWrite(FILE *F, upstring str){
    if(!str.length) return;
    char *s = upToString(str);
    if(!s) return;
    fputs(s,F);
    free(s);
}

//Write to console
void upConsoleWrite(upstring s){
    upWrite(stdout,s);
}
void upConsoleWriteln(upstring s){
    upConsoleWrite(s);
    printf("\n");
}

//Read until char
upstring upReadC(FILE *f,char c){
    upstring res = nls;
    unsigned short add=512;
    char *t,*s = upNew(add,char);
    unsigned long i=0;
    char ch[1];
    while(fread(ch,1,1,f)  && ((*ch)^c)){
        s[i] = ch[0];
        ++i;
        if(i%add==0){
            t = realloc(s,(i+add)*sizeof(char));
            if(t)
                s = t;
            else{
                free(s);
                return res;
            }
        }
    }
    if(i>0)
        s[i++] ='\0';
    else
        s[0] = '\0';
    res = upString(s);
    free(s);
    return res;
}

//Read until N symbols
upstring upReadN(FILE *f,unsigned int n){
    unsigned char c,count,add = 64;
    upstring res = nls;
    unsigned int length = 0;
    unsigned sint *t,*text = upNew(add,unsigned sint);
    char ch[6];
    while((fread(ch,1,1,f))){
        c=ch[0];
        count=0;

        while((c<<count) & 0x80)
            ++count;
        if(count>1)
            --count;
        else if(count==1){
            free(text);
            return nls;
        }
        c=fread(ch+1,1,count,f);
        if(c!=count){
            free(text);
            return nls;
        }
        text[length++]=ord(ch,&count);
        if(length == n)
            break;
        if(length%add==0 && length>0){
            t = realloc(text,(length+add)*sizeof(int));
            if(t)
                text = t;
            else{
                free(text);
                return nls;
            }
        }
    }
    if(length>0)
        t = realloc(text,(length)*sizeof(int));
    else{
        free(text);
        return nls;
    }
    if(t)
        text = t;
    else{
        free(text);
        return nls;
    }
    res.text = text;
    res.length = length;
    return res;
}

upstring upRead(FILE *f){
    return upReadC(f,'\0');
}
upstring upConsoleRead(){
    return upReadC(stdin,'\0');
}
upstring upConsoleReadln(){
    return upReadC(stdin,'\n');
}
