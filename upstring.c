#include "upstring.h"

//Coonstructer
upstring upString(char *str){
    upstring result;
    char *p=str;
    unsigned int add=512,size=0;
    unsigned sint *tt,*temp;
    unsigned char c=0;

    temp = upNew(add,unsigned sint);
    while(p[0]){
        temp[size++] = ord(p,&c);
        p+=c;
        if(size%add==0){
            tt = (unsigned sint*)realloc((void*)temp,(size+add)*sizeof(unsigned sint));
            if(tt)
                temp = tt;
            else{
                free(temp);
                return nls;
            }
        }

    }
    result.text = (unsigned sint*)realloc((void*)temp,size*sizeof(unsigned sint));
    result.length = size;
    return result;
}
//Length
unsigned int upLength(upstring str){
    return str.length;
}
//Get real byte size
unsigned int upCount(upstring str){
    unsigned int i,count = 0;

    upLoop(i,0,str.length){
        if(str.text[i]<=0x7F)
            count+=1;
        else if(str.text[i]<=0x7FF)
            count+=2;
        else if(str.text[i]<=0xFFFF)
            count+=3;
        else if(str.text[i]<=0x1FFFFF)
            count+=4;
        else if(str.text[i]<=0x3FFFFFF)
            count+=5;
        else if(str.text[i]<=0x7FFFFFFF)
            count+=6;
    }

    if(count<str.length)
        count=0;
    return count;
}
//Convert back to UTF8
char *upToString(upstring str){
    unsigned int i,sz = upCount(str);
    unsigned char c;
    char *res,*p;
    if(!sz)
        return 0;
    ++sz;
    res = upNew(sz,char);
    p = res;
    upLoop(i,0,str.length){
        chr(str.text[i],p,&c);
        p+=c;
    }
    res[sz-1] = 0;
    return res;
}
//Copy string part
upstring upCopy(upstring src,unsigned int start,unsigned int count){
    upstring res;
    void *p = src.text+start;
    void *mem = malloc(count*sizeof(sint));
    if(start>src.length){
        res.text = 0;
        res.length = 0;
        return res;
    }
    if(start+count>src.length){
        count = src.length - start;
    }

    memcpy(mem,p,count*sizeof(unsigned sint));
    res.length=count;
    res.text = (unsigned sint*)mem;
    return res;
}
//Clone strings
upstring upClone(upstring src){
    return upCopy(src,0,src.length);
}
/**Destructors*/
//Clean string
void upReset(upstring *str){
    free(str->text);
    str->length = 0;
}
int _upClean(upstring str, char command){
    static int count = 0;
    static int current= 16;
    static unsigned sint **array = 0;
    unsigned sint **temp = 0;
    int i;

    if(command==0){
        if(count==0)
            array = (unsigned sint **)malloc(current*sizeof(sint**));
        if(count==current){
            current += 16;
            temp = array;
            array = (unsigned sint**)realloc((void*)temp,current*sizeof(int**));
        }
        array[count++] = str.text;
    }

    else if(command==1){

        upLoop(i,0,count)
            free(array[i]);
        count = 0;
        current = 16;
        free(array);
        return i;
    }

    return 0;
}
//Clean all
int upUnsetAll(){
    upstring s;
    return _upClean(s,1);
}
//Register for remove
void upUnsetSoon(upstring s){
    _upClean(s,0);
}

/**Temp strings*/
upstring tpString(char *src){
    upstring res = upString(src);
    upUnsetSoon(res);
    return res;
}

upstring tpCopy(upstring src,unsigned int start,unsigned int count){
    upstring res = upCopy(src,start,count);
    upUnsetSoon(res);
    return res;
}

upstring tpClone(upstring src){
    upstring res = upClone(src);
    upUnsetSoon(res);
    return res;
}
