#include "include/vga.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/timer.h"
#include "include/keyboard.h"

void kernelMain()
{
    initGDT();
    initIDT();
    initTimer();
    initKeyboard();

    ResetVGA();

    for (;;)
        ;
}
