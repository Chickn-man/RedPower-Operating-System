#ifndef _STRING2_H
#define _STRING2_H

void strcatc(char *ds, char c);
void strdelc(char *str);
unsigned int hextoi(char *str);
char *itohex(unsigned int num);

int atoi(char *str);
char *itoa(int num, char *buffer, int radix);

#endif 