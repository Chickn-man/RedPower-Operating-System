#ifndef _DISK_H
#define _DISK_H

unsigned char* readSector(char letter, unsigned short sector, unsigned char* buffer);
unsigned char* writeSector(char letter, unsigned short sector, unsigned char* buffer);

unsigned char* readDiskName(char letter);
unsigned char* writeDiskName(char letter, char *name);

unsigned char* readDiskSerial(char letter);

#endif