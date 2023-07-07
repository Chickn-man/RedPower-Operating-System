#ifndef _FILESYSTEM_TABLE_H
#define _FILESYSTEM_TABLE_H

typedef struct {
    unsigned char boot;
    unsigned char startHead;
    unsigned char startSector : 6;
    unsigned short startCylinder : 10;
    unsigned char systemID;
    unsigned char endHead;
    unsigned char endSector : 6;
    unsigned short endCylinder : 10;
    unsigned long lbaStart;
    unsigned long lbaEnd;
} tableEntry;

#define MBR_NOT_BOOTABLE 0x0
#define MBR_BOOTABLE 0x80

// System id values valid in rpos

#define MBR_FAT 0x01 // not implemented
#define MBR_FAT_16_SMALL 0x04 // not implemented
#define MBR_FAT_16_BIG 0x06 // not implemented
#define MBR_FAT_32 0x0b // not implemented
#define MBR_FAT_32_LBA 0x0c // not implementedbg
#define MBR_FAT_16_LBA 0x0e // not implemented

typedef struct {
    unsigned char head;
    unsigned char sector : 6;
    unsigned short cylinder : 10;
} chs;

unsigned long chstolba(chs *input);
chs *lbatochs(unsigned long input);

#endif