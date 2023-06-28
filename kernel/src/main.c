#include <mmu.h>
#include <globals.h>
#include <window.h>
#include <conio.h>
#include "string.h"

int main(void) {
    unsigned char i;
    char c;
    char input[128];
    char command[64];

    cputs("Hellorld!\n");

    cputc('>');
    
    while (1) {
        c = cgetc();
        if (c == 0x8) strdelc(input), cbkspc(), c = 0; else cputc(c);

        if (c == '\r' || c == '\n') {
            if (strlen(input) != 0) {
                strcpy(command, strtok(input, " "));

                if (strcmp(command, "cls") == 0) {
                    cls();

                } else if (strcmp(command, "ascii") == 0) {
                    for (i = 0; i < 255; i++) cputc2(i);
                    cputc('\n');

                } else if (strcmp(command, "peek") == 0) {
                    // grab address from input, read value at addr and print value in hex
                    cputs(itohex(*(unsigned char*)hextoi(strtok(0, " "))));
                    cputc('\n');

                } else if (strcmp(command, "poke") == 0) {
                    // grab address from input, grab hex value from input, and write value to address
                    *(unsigned char *)hextoi(strtok(0, " ")) = (unsigned char)hextoi(strtok(0, " "));
                    cputc('\n');

                } else if (strcmp(command, "jump") == 0) {
                    // grab address from input, jump to address (jsr)
                    void (*jump)(void) = (void (*)(void))(hextoi(strtok(0, " ")));
                    (*jump)();

                } else {
                    cputs("command not found\n");

                }

            }
            for (i = 0; i < 128; i++) input[i] = 0;
            for (i = 0; i < 64; i++) command[i] = 0;

            cputc('>');

        } else strcatc(input, c);

    }
    
    return 0;

}