#include "disk.h"
#include "globals.h"
#include "window.h"
#include <mmu.h>
#include "asm/asm.h"

/* reads sector "sector" of drive "letter" into "buffer" */
// returns a pointer to the buffer if successful.
// returns 1 if the drive letter is invalid.
// returns 2 if the read failed.
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

unsigned char* writeSector(char letter, unsigned short sector, unsigned char* buffer);

unsigned char* readDiskName(char letter);
unsigned char* writeDiskName(char letter, char *name);

unsigned char* readDiskSerial(char letter);