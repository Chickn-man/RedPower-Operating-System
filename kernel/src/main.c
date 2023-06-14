#include <mmu.h>
#include <window.h>

void print(char *string);

int main() {
    print("Hellorld!");

    return 0;
}

int print_i = 0;

void print(char *string) {
    setMappedRedbusDev(1);

    for (print_i = 0; string[print_i] != 0; print_i++) {
        screenBuffer[print_i] = string[print_i];
    }

}