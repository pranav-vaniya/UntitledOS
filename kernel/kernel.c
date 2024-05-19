#include "include/vga.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/timer.h"

void kernelMain()
{
    initGDT();
    initIDT();
    initTimer();

    ResetVGA();

    for (;;)
        ;
}
