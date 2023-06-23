#include <mmu.h>
#include <globals.h>
#include <window.h>
#include <conio.h>
#include <string.h>

int main(void) {
    unsigned char i;
    char c;
    char input[128];

    cputs("Hellorld!\n");
    
    while (1) {
        c = cgetc();
        if (c == 0x8) strdelc(input), cbkspc(), c = 0; else cputc(c);

        if (c == '\r') {
            if (strlen(input) != 0) {
                if (strcmp(input, "cls") == 0) {
                    cls();
                } else {
                    cputs("command not found\n");
                }
            }

            for (i = 0; i < 128; i++) input[i] = 0;

            cputc('>');
        } else strcatc(c, input);

    }

    return 0;
}