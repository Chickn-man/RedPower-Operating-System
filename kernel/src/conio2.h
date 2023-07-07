#ifndef _CONIO2_H
#define _CONIO2_H

void blitShift(unsigned char sx, unsigned char sy, unsigned char dx, unsigned char dy, unsigned char w, unsigned char h);
void blitFill(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char character);

void clrscr(void);
void gotoxy(unsigned char x, unsigned char y);
void gotox(unsigned char x);
void gotoy(unsigned char y);

unsigned char wherex(void);
unsigned char wherey(void);

void cputc(char c);
void cputc2(char c);
void cputs(char *s);
char cgetc(void);
void cbkspc(void);

#endif