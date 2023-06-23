#include <string.h>

unsigned short strlen(char *string) {
    unsigned short len;

    for (len = 0; string[len] != 0; len++);
    return len;
}

void strcpy(char *src, char *dst) {
    unsigned short i;

    for (i = 0; src[i] != 0; i++) dst[i] = src[i];
}

void strcat(char *src, char *dst) {
    unsigned short len = strlen(dst);

    unsigned short i;

    for (i = 0; src[i] != 0; i++) dst[len + i] = src[i];
}

void strcatc(char c, char *dst) {
    unsigned short len = strlen(dst);

    dst[len++] = c;
    dst[len] = 0;
}

unsigned char strcmp(char *s1, char *s2) {
    char *p1 = s1;
    char *p2 = s2;

    while (*p1 && (p1 == p2)) p1++, p2++;

    return *p1 - *p2;
}

void strdelc(char *str) {
    unsigned short len = strlen(str);

    if (!len) return;

    str[len - 1] = 0;
}