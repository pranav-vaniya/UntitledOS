#include "include/stdint.h"
#include "include/util.h"
#include "include/idt.h"
#include "include/vga.h"
#include "include/timer.h"
#include "include/stdio.h"

uint64 ticks;
const uint32 freq = 100;

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
