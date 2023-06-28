#ifndef _STRING_H
#define _STRING_H

unsigned short strlen(char *string);
void strcpy(char *dst, char *src);
void strcat(char *dst, char *src);
void strcatc(char *ds, char c);
int strcmp(char *s1, char *s2);
void strdelc(char *str);
char *strtok(char *str, char *c);
unsigned int hextoi(char *str);
char *itohex(unsigned int num);

int atoi(char *str);
char *itoa(int num);

#endif 