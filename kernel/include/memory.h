#pragma once

extern uint32 initial_page_dir[1024];

#define KERNEL_START 0xC0000000
#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_WRITE (1 << 1)

void initMemory(uint32 memHigh, uint32 physicalAllocStart);
void pmm_init(uint32 memLow, uint32 memHigh);
void invalidate(uint32 vaddr);
