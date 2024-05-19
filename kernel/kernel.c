#include "include/vga.h"
#include "include/gdt.h"
#include "include/idt.h"

void kernelMain()
{
    initGDT();
    initIDT();

    ResetVGA();

    int a = 556;
    printd(a);
}
