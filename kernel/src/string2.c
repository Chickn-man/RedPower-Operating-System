#include "string2.h"
#include <string.h>

void strcatc(char *dst, char c) {
    unsigned short len = strlen(dst);

    dst[len++] = c;
    dst[len] = 0;

}

void strdelc(char *str) {
    unsigned short len = strlen(str);

    if (!len) return;

    str[len - 1] = 0;

}

unsigned int hextoi(char *str) {
    unsigned int val = 0;
    unsigned char i;

    for (i = 0; str[i]; i++) {
        if (str[i] >= '0' && str[i] <= '9') str[i] = str[i] - '0';
        else if (str[i] >= 'a' && str[i] <= 'f') str[i] = str[i] - 'a' + 10;
        val = (val << 4) | (str[i] & 0xf);
    }
    
    return val;
        
}

char *itohex(unsigned int num) {
    unsigned char i = 7;
    unsigned char s = 0;
    unsigned int n = num;
    char buffer[8];

    while (n > 0) {
        buffer[i] = "0123456789abcdef"[n % 16];
        i--;
        n = n / 16;

    }

    while (++i < 8) {
        buffer[s++] = buffer[i];

    }

    buffer[s] = 0;

    return buffer;

}