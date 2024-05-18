#include "include/vga.h"
#include "include/gdt.h"
#include "include/idt.h"

void kernelMain()
{
    initGDT();
    initIDT();

    ResetVGA();

    print("Added IDT\n");

    int a = 1/0;

    print("System did not print this. Did it?.");
}
