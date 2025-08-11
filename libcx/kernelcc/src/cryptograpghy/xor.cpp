#include <cryptography/xor.h>

char* encrypt( char* msg,char key){
    INTEGER i = 0;
    while(msg[i] != '\0'){
        msg[i] ^= key;
        ++i;
    }
    return msg;
}