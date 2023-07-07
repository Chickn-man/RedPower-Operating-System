// header file for fat12 functions

#ifndef _FILESYSTEM_FAT_H
#define _FILESYSTEM_FAT_H

typedef struct {
    unsigned long entryPoint : 24;
    char oemID[8]; // non zero terminated string
    unsigned short bytesPerSector;
    unsigned char sectorsPerCluster;
    unsigned short reservedSectors;
    unsigned char fatCopies;
    unsigned short rootEntries;
    unsigned short smallNumberOfSectors;
    unsigned char mediaDescriptor;
    unsigned short sectorsPerFat;
    unsigned short sectorsPerTrack;
    unsigned short numberOfHeads;
    unsigned long hiddenSectors;
    unsigned long largeNumberOfSectors;
    unsigned char driveNumber;
    unsigned char reserved;
    unsigned char extendedBootSignature;
    unsigned long serial;
    char lable[11]; // non zero terminated string
    char type[8]; // non zero terminated string
    unsigned char bootCode[448];
    unsigned short bootSignature;
} fatBootSector;

#endif