#ifndef _CONIO_H
#define _CONIO_H

void blitShift(unsigned char sx, unsigned char sy, unsigned char dx, unsigned char dy, unsigned char w, unsigned char h);
void blitFill(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char character);

void cls(void);
void gotoXY(unsigned char x, unsigned char y);
void gotoX(unsigned char x);
void gotoY(unsigned char y);

unsigned char whereX(void);
unsigned char whereY(void);

void cputc(char c);
void cputs(char *s);
char cgetc(void);
void cbkspc(void);

#endif