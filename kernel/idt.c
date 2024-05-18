#include "include/stdint.h"
#include "include/util.h"
#include "include/vga.h"
#include "include/idt.h"

struct idt_entry_struct idt_entries[256];
struct idt_ptr_struct idt_ptr;

extern void idt_flush(uint32);

void initIDT()
{
    idt_ptr.limit = sizeof(struct idt_entry_struct) * 256 - 1;
    idt_ptr.base = (uint32)&idt_entries;

    memset(&idt_entries, 0, sizeof(struct idt_entry_struct) * 256);

    outPortB(0x20, 0x11);
    outPortB(0xA0, 0x11);

    outPortB(0x21, 0x20);
    outPortB(0xA1, 0x28);

    outPortB(0x21, 0x04);
    outPortB(0xA1, 0x02);

    outPortB(0x21, 0x01);
    outPortB(0xA1, 0x01);

    outPortB(0x21, 0x0);
    outPortB(0xA1, 0x0);

    setIDTGate(0, (uint32)isr0, 0x08, 0x8E);
    setIDTGate(1, (uint32)isr1, 0x08, 0x8E);
    setIDTGate(2, (uint32)isr2, 0x08, 0x8E);
    setIDTGate(3, (uint32)isr3, 0x08, 0x8E);
    setIDTGate(4, (uint32)isr4, 0x08, 0x8E);
    setIDTGate(5, (uint32)isr5, 0x08, 0x8E);
    setIDTGate(6, (uint32)isr6, 0x08, 0x8E);
    setIDTGate(7, (uint32)isr7, 0x08, 0x8E);
    setIDTGate(8, (uint32)isr8, 0x08, 0x8E);
    setIDTGate(9, (uint32)isr9, 0x08, 0x8E);
    setIDTGate(10, (uint32)isr10, 0x08, 0x8E);
    setIDTGate(11, (uint32)isr11, 0x08, 0x8E);
    setIDTGate(12, (uint32)isr12, 0x08, 0x8E);
    setIDTGate(13, (uint32)isr13, 0x08, 0x8E);
    setIDTGate(14, (uint32)isr14, 0x08, 0x8E);
    setIDTGate(15, (uint32)isr15, 0x08, 0x8E);
    setIDTGate(16, (uint32)isr16, 0x08, 0x8E);
    setIDTGate(17, (uint32)isr17, 0x08, 0x8E);
    setIDTGate(18, (uint32)isr18, 0x08, 0x8E);
    setIDTGate(19, (uint32)isr19, 0x08, 0x8E);
    setIDTGate(20, (uint32)isr20, 0x08, 0x8E);
    setIDTGate(21, (uint32)isr21, 0x08, 0x8E);
    setIDTGate(22, (uint32)isr22, 0x08, 0x8E);
    setIDTGate(23, (uint32)isr23, 0x08, 0x8E);
    setIDTGate(24, (uint32)isr24, 0x08, 0x8E);
    setIDTGate(25, (uint32)isr25, 0x08, 0x8E);
    setIDTGate(26, (uint32)isr26, 0x08, 0x8E);
    setIDTGate(27, (uint32)isr27, 0x08, 0x8E);
    setIDTGate(28, (uint32)isr28, 0x08, 0x8E);
    setIDTGate(29, (uint32)isr29, 0x08, 0x8E);
    setIDTGate(30, (uint32)isr30, 0x08, 0x8E);
    setIDTGate(31, (uint32)isr31, 0x08, 0x8E);

    setIDTGate(32, (uint32)irq0, 0x08, 0x8E);
    setIDTGate(33, (uint32)irq1, 0x08, 0x8E);
    setIDTGate(34, (uint32)irq2, 0x08, 0x8E);
    setIDTGate(35, (uint32)irq3, 0x08, 0x8E);
    setIDTGate(36, (uint32)irq4, 0x08, 0x8E);
    setIDTGate(37, (uint32)irq5, 0x08, 0x8E);
    setIDTGate(38, (uint32)irq6, 0x08, 0x8E);
    setIDTGate(39, (uint32)irq7, 0x08, 0x8E);
    setIDTGate(40, (uint32)irq8, 0x08, 0x8E);
    setIDTGate(41, (uint32)irq9, 0x08, 0x8E);
    setIDTGate(42, (uint32)irq10, 0x08, 0x8E);
    setIDTGate(43, (uint32)irq11, 0x08, 0x8E);
    setIDTGate(44, (uint32)irq12, 0x08, 0x8E);
    setIDTGate(45, (uint32)irq13, 0x08, 0x8E);
    setIDTGate(46, (uint32)irq14, 0x08, 0x8E);
    setIDTGate(47, (uint32)irq15, 0x08, 0x8E);

    setIDTGate(128, (uint32)isr128, 0x08, 0x8E);
    setIDTGate(177, (uint32)isr177, 0x08, 0x8E);

    idt_flush((uint32)&idt_ptr);
}

void setIDTGate(uint8 num, uint32 base, uint16 sel, uint8 flags)
{
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags | 0x60;
}

unsigned char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Co-Processor",
    "Double Fault",
    "Co-Processor Segment Overrun",
    "Bad TSS",
    "Segment not Present",
    "Stack Fault",
    "Generation Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Co-Processor Fault",
    "Alignment Fault",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"};

void isr_handler(struct InterruptRegisters *regs)
{
    if (regs->int_no < 32)
    {
        print(exception_messages[regs->int_no]);
        print("\n");
        print("Exception! System Halted\n");
        for (;;)
            ;
    }
}

void *irq_routines[16] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0};

void irq_install_handler(int irq, void (*handler)(struct InterruptRegisters *r))
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

void irq_handler(struct InterruptRegisters *regs)
{
    void (*handler)(struct InterruptRegisters *regs);
    handler = irq_routines[regs->int_no - 32];

    if(handler){
        handler(regs);
    }

    if(regs->int_no>=40){
        outPortB(0xA0, 0x20);
    }

    outPortB(0x20, 0x20);
}
