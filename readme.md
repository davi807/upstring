```c
#include "upstring/upstring.h"

int main(){
    upstring str = upString("Բարև"); //Convert to short integer
    upstring ntt = upString("աշխարհ");
    upAppend(&str,ntt); // str+ntt
    upInsert(tpString(" "),&str,4,1); //Insert one char
    upConsoleWriteln(str); //Output str
    upUnsetAll(); //For tpString
    return 0;
}
```
##For more info read header files ```upstring.h``` and ```utf8.h```