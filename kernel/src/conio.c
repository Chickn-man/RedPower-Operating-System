#include <conio.h>
#include <globals.h>
#include <window.h>
#include <asm.h>
#include <mmu.h>

void blitShift(unsigned char sx, unsigned char sy, unsigned char dx, unsigned char dy, unsigned char w, unsigned char h) {
    setMappedRedbusDev(screenID);

    blitX = sx;
    blitY = sy;

    blitXOffset = dx;
    blitYOffset = dy;

    blitWidth = w;
    blitHeight = h;

    blitMode = BLIT_SHIFT;
    
    while (blitMode == BLIT_SHIFT) {
        wait(); 
    }
}

void blitFill(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char character) {
    setMappedRedbusDev(screenID);

    blitChar = character;

    blitXOffset = x;
    blitYOffset = y;

    blitWidth = w;
    blitHeight = h;

    blitMode = BLIT_FILL;
    
    while (blitMode == BLIT_FILL) {
        wait(); 
    }
}

void cls(void) {
    blitFill(0, 0, 80, 50, ' ');
    gotoXY(0, 0);
}

void gotoXY(unsigned char x, unsigned char y) {
    setMappedRedbusDev(screenID);

    cursorX = x;
    cursorY = y;
}
void gotoX(unsigned char x) {
    setMappedRedbusDev(screenID);

    cursorX = x;
}
void gotoY(unsigned char y) {
    setMappedRedbusDev(screenID);

    cursorY = y;
}

unsigned char whereX(void) {
    setMappedRedbusDev(screenID);

    return cursorX;
}
unsigned char whereY(void) {
    setMappedRedbusDev(screenID);

    return cursorY;
}

/* puts a character c at the cursor position */
void cputc(char c) {
    setMappedRedbusDev(screenID);

    screenRow = cursorY;

    if (c != '\n' && c != '\r') screenBuffer[cursorX] = c;

    cursorX = cursorX + 1;

    if (cursorX > 79 || c == '\n' || c == '\r') {
        cursorX = 0;

        if (cursorY >= 49) {
            /* scroll terminal */
            blitShift(0, 1, 0, 0, 80, 49);

            blitFill(0, 49, 80, 1, ' ');
        } else {
            cursorY = cursorY + 1;
        }
    }
}

/* puts a character c at the cursor position | no \n or \r support */
void cputc2(char c) {
    setMappedRedbusDev(screenID);

    screenRow = cursorY;

    if (c != '\n' && c != '\r') screenBuffer[cursorX] = c;

    cursorX = cursorX + 1;

    if (cursorX > 79) {
        cursorX = 0;

        if (cursorY >= 49) {
            /* scroll terminal */
            blitShift(0, 1, 0, 0, 80, 49);

            blitFill(0, 49, 80, 1, ' ');
        } else {
            cursorY = cursorY + 1;
        }
    }
}

void cputs(char *s) {
    while (*s != 0) {
        cputc(*s++);
    }
}

/* gets a character from the keyboard */
// waits if no charater is available
// i have no clue how this works
char cgetc(void) {
    char key;

    setMappedRedbusDev(screenID);

    cursorMode = CURSOR_BLINK;
    
    while (!(keyBuffer != keyPosition)) wait();

    key = keyStart;

    keyBuffer = keyBuffer + 1;
    if (keyBuffer > 0x10) keyBuffer = 0;

    cursorMode = CURSOR_HIDDEN;
    return key;
}

void cbkspc(void) {
    setMappedRedbusDev(screenID);

    if (cursorX == 0 && cursorY == 0) return;

    cursorX = cursorX - 1;
    if (cursorX == 255) gotoXY(79, cursorY - 1);

    screenRow = cursorY;
    screenBuffer[cursorX] = ' ';
}

void cdelc(void) {
    setMappedRedbusDev(screenID);

    screenRow = cursorY;
    screenBuffer[cursorX] = ' ';
}
