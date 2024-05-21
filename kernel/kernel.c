#include "include/stdint.h"
#include "include/stdio.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/vga.h"
#include "include/timer.h"
#include "include/keyboard.h"
#include "include/multiboot.h"
#include "include/memory.h"
#include "include/kmalloc.h"
#include "include/shell.h"

void kernelMain(uint32 magic, struct multiboot_info *bootInfo)
{
    printf("Untitled OS. Doodle Shell.\n");

    uint32 mod1 = *(uint32 *)(bootInfo->mods_addr + 4);
    uint32 physicalAllocStart = (mod1 + 0xFFF) & ~0xFFF;

    initGDT();
    initIDT();
    initTimer();
    initKeyboard();
    initMemory(bootInfo->mem_upper * 1024, physicalAllocStart);
    initKmalloc(0x1000);
    initShell();

    for (;;)
        ;
}
