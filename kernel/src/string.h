#ifndef _STRING_H
#define _STRING_H

unsigned short strlen(char *string);
void strcpy(char *src, char *dst);
void strcat(char *src, char *dst);
void strcatc(char c, char *dst);
unsigned char strcmp(char *s1, char *s2);
void strdelc(char *str);

#endif 