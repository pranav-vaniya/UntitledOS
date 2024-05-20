#pragma once

#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_WRITE (1 << 1)
#define PAGE_FLAG_OWNER (1 << 9)
#define KERNEL_START 0xC0000000
#define KERNEL_MALLOC 0xD0000000
#define REC_PAGEDIR ((uint32 *)0xFFFFF000)
#define REC_PAGETABLE(i) ((uint32 *)(0xFFC00000 + ((i) << 12)))

extern uint32 initial_page_dir[1024];

void initMemory(uint32 memHigh, uint32 physicalAllocStart);
void pmm_init(uint32 memLow, uint32 memHigh);
void invalidate(uint32 vaddr);
uint32 pmmAllocPageFrame();
uint32 *memGetCurrentPageDir();
void memChangePageDir(uint32 *pd);
void syncPageDirs();
void memMapPage(uint32 virtualAddr, uint32 physAddr, uint32 flags);
