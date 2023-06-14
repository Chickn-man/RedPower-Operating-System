#ifndef _WINDOW_H
#define _WINDOW_H

/* pointers */

#define WINDOW 0xff00
#define SCREEN_ROW WINDOW + 0x0
#define CURSOR_X WINDOW + 0x1
#define CURSOR_Y WINDOW + 0x2
#define CURSOR_MODE WINDOW + 0x3
#define KEY_BUFFER WINDOW + 0x4
#define KEY_POSITION WINDOW + 0x5
#define KEY_START WINDOW + 0x6
#define BLIT_MODE WINDOW + 0x7
#define BLIT_X WINDOW + 0x8
#define BLIT_Y WINDOW + 0x9
#define BLIT_X_OFFSET WINDOW + 0xa
#define BLIT_Y_OFFSET WINDOW + 0xb
#define BLIT_WIDTH WINDOW + 0xc
#define BLIT_HEIGHT WINDOW + 0xd
#define SCREEN_BUFFER WINDOW + 0x10

#define IO_BUFFER WINDOW
#define IO_LATCH WINDOW + 0x2

#define DISK_BUFFER WINDOW
#define DISK_SECTOR WINDOW + 0x80
#define DISK_COMMAND WINDOW + 0x82


/* variable macros */

#define screenRow *((unsigned char *)SCREEN_ROW)
#define cursorX *((unsigned char *)CURSOR_X)
#define cursorY *((unsigned char *)CURSOR_Y)
#define cursorMode *((unsigned char *)CURSOR_MODE)
#define keyBuffer *((unsigned char *)KEY_BUFFER)
#define keyPosition *((unsigned char *)KEY_POSITION)
#define keyStart *((unsigned char *)KEY_START)
#define blitMode *((unsigned char *)BLIT_MODE)
#define blitX *((unsigned char *)BLIT_X)
#define blitY *((unsigned char *)BLIT_Y)
#define blitXOffset *((unsigned char *)BLIT_X_OFFSET)
#define blitYOffset *((unsigned char *)BLIT_Y_OFFSET)
#define blitWidth *((unsigned char *)BLIT_WIDTH)
#define blitHeight *((unsigned char *)BLIT_HEIGHT)
#define screenBuffer ((unsigned char *)SCREEN_BUFFER)

#define ioExpanderBuffer *((unsigned short *)IO_BUFFER)
#define ioExpanderLatch *((unsigned short *)IO_LATCH)

#define diskBuffer ((unsigned char *)DISK_BUFFER)
#define diskSector *((unsigned short *)DISK_SECTOR)
#define diskCommand *((unsigned char *)DISK_COMMAND)

#endif