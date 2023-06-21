#include <mmu.h>
#include <globals.h>
#include <window.h>
#include <conio.h>

void print(char *string);

int main(void) {
    char c;

    cputs("Hellorld!\n");

    while (1) {
        c = cgetc();
        if (c == 0x8) cbkspc(); else cputc(c);
    }

    return 0;
}