#include "disk.h"
#include "globals.h"
#include "window.h"
#include <mmu.h>
#include "asm/asm.h"
#include "string.h"

// reads logical sector "sector" of drive "letter" into "buffer".
// returns "buffer" if successful.
// returns 1 if the drive letter is invalid.
// returns 2 if the read failed for any physical sector.
unsigned char* readSector(char letter, unsigned short sector, unsigned char* buffer) {
    unsigned short i = 0;
    unsigned char j;
    unsigned char k;

    if (letter != 'a' && letter != 'A') return (unsigned char *)1;

    setMappedRedbusDev(driveA_ID);

    sector *= 4;

    for (j = 0; j < 4; j++) {
        diskSector = sector + j;
        diskCommand = DISK_READ;

        wait();

        if (diskCommand == DISK_FAILURE) return (unsigned char *)2;

        for (k = 0; k < 128; k++) {
            buffer[i++] = diskBuffer[k];
        } 
    }

    return buffer;

}

// writes "buffer" into logical sector "sector" of drive "letter".
// returns "buffer" if successful.
// returns 1 if the drive letter is invalid.
// returns 2 if the write failed for any physical sector.
unsigned char* writeSector(char letter, unsigned short sector, unsigned char* buffer) {
    unsigned short i = 0;
    unsigned char j;
    unsigned char k;

    if (letter != 'a' && letter != 'A') return (unsigned char *)1;

    setMappedRedbusDev(driveA_ID);

    sector *= 4;

    for (j = 0; j < 4; j++) {
        for (k = 0; k < 128; k++) {
            diskBuffer[k] = buffer[i++];
        } 

        diskSector = sector + j;
        diskCommand = DISK_WRITE;

        wait();

        if (diskCommand == DISK_FAILURE) return (unsigned char *)2;

    }

    return buffer;

}

// reads the name of drive "letter" into "buffer".
// returns "buffer" if successful.
// returns 1 if the drive letter is invalid.
// returns 2 if the read failed.
char* readDiskName(char letter, char *buffer) {
    if (letter != 'a' && letter != 'A') return (char *)1;

    setMappedRedbusDev(driveA_ID);

    diskCommand = DISK_READ_NAME;

    wait();

    if (diskCommand == DISK_FAILURE) return (char *)2;

    strcpy(buffer, diskBuffer);

    return buffer;

}

// writes "name" to drive "letter"
// returns "name" if successful.
// returns 1 if the drive letter is invalid.
// returns 2 if the write failed.
char* writeDiskName(char letter, char *name) {
    unsigned char i;

    if (letter != 'a' && letter != 'A') return (char *)1;

    setMappedRedbusDev(driveA_ID);

    for (i = 0; i < 128; i++) diskBuffer[i] = 0;

    strcpy(diskBuffer, name);

    diskCommand = DISK_WRITE_NAME;

    wait();

    if (diskCommand == DISK_FAILURE) return (char *)2;

    return name;

}

// reads the serial number of drive "letter" into "buffer".
// returns "buffer" if successful.
// returns 1 if the drive letter is invalid.
// returns 2 if the read failed.
char* readDiskSerial(char letter, char *buffer) {
    if (letter != 'a' && letter != 'A') return (char *)1;

    setMappedRedbusDev(driveA_ID);

    diskCommand = DISK_READ_SERIAL;

    wait();

    if (diskCommand == DISK_FAILURE) return (char *)2;

    strcpy(buffer, diskBuffer);

    return buffer;

}
