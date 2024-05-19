#include "include/vga.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/timer.h"
#include "include/keyboard.h"
#include "include/stdio.h"
#include "include/stdint.h"

void kernelMain()
{
    initGDT();
    initIDT();
    initTimer();
    initKeyboard();

    int num = 45564;
    printf("Hello, World %d!\n", num);

    putc('z');

    for (;;)
        ;
}
