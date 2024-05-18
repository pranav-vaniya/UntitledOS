#include "include/vga.h"
#include "include/gdt.h"

void kernelMain()
{
    initGDT();

    ResetVGA();

    print("Hello, World!\n");
}
