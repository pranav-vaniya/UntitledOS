#include "include/stdint.h"
#include "include/util.h"
#include "include/idt.h"
#include "include/vga.h"
#include "include/timer.h"
#include "include/stdio.h"

// If we keep freq = 1000 than 1000 ticks are nearly equal to 1 second. Do not use for strict timing.

uint64 ticks;
const uint32 freq = 1000;

void onIrq0(struct InterruptRegisters *regs)
{
    ticks++;
    // print("a ");
}

void initTimer()
{
    ticks = 0;
    irq_install_handler(0, &onIrq0);

    uint32 divisor = 1193180 / freq;

    outPortB(0x43, 0x36);
    outPortB(0x40, (uint8)(divisor & 0xFF));
    outPortB(0x40, (uint8)((divisor >> 8) & 0xFF));
}

uint64 time()
{
    return ticks;
}

// Definitely not the right way to implement the sleep function
void sleep(uint64 milliseconds)
{
    uint64 target = ticks + milliseconds;

    while (ticks < target)
    {
        asm volatile("hlt");
    }
}
