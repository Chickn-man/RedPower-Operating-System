#ifndef _DISK_H
#define _DISK_H

unsigned char* readSector(char letter, unsigned short sector, unsigned char* buffer);
unsigned char* writeSector(char letter, unsigned short sector, unsigned char* buffer);

char* readDiskName(char letter, char* buffer);
char* writeDiskName(char letter, char *name);

char* readDiskSerial(char letter, char* buffer);

#endif