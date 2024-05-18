#include "include/gdt.h"
#include "include/stdint.h"
#include "include/util.h"

extern void gdt_flush(uint32);
extern void tss_flush();

struct gdt_entry_struct gdt_entries[6];
struct gdt_ptr_struct gdt_ptr;
struct tss_entry_struct tss_entry;

void initGDT()
{
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 6) - 1;
    gdt_ptr.base = (uint32)&gdt_entries;

    setGDTGate(0, 0, 0, 0, 0);
    setGDTGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    setGDTGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    setGDTGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    setGDTGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    writeTSS(5, 0x10, 0x0);

    gdt_flush((uint32)&gdt_ptr);
    tss_flush();
}

void setGDTGate(uint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit = (limit & 0xFFFF);
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);

    gdt_entries[num].access = access;
}

void writeTSS(uint32 num, uint16 ss0, uint32 esp0)
{
    uint32 base = (uint32)&tss_entry;
    uint32 limit = base + sizeof(tss_entry);

    setGDTGate(num, base, limit, 0xE9, 0x00);
    memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0 = ss0;
    tss_entry.esp0 = esp0;

    tss_entry.cs = 0x08 | 0x3;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
}
