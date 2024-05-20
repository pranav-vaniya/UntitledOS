#include "include/stdint.h"
#include "include/multiboot.h"
#include "include/stdio.h"
#include "include/util.h"
#include "include/memory.h"

static uint32 pageFrameMin;
static uint32 pageFrameMax;
static uint32 totalAlloc;

#define NUM_PAGES_DIRS 256
#define NUM_PAGE_FRAMES (0x100000000 / 0x1000 / 8)

uint8 physicalMemoryBitmap[NUM_PAGE_FRAMES / 8];

static uint32 pageDirs[NUM_PAGES_DIRS][1024] __attribute__((aligned(4096)));
static uint8 pageDirUsed[NUM_PAGES_DIRS];

void pmm_init(uint32 memLow, uint32 memHigh)
{
    pageFrameMin = CEIL_DIV(memLow, 0x1000);
    pageFrameMax = memHigh / 0x1000;
    totalAlloc = 0;

    memset(physicalMemoryBitmap, 0, sizeof(physicalMemoryBitmap));
}

void initMemory(uint32 memHigh, uint32 physicalAllocStart)
{
    initial_page_dir[0] = 0;

    invalidate(0);

    initial_page_dir[1023] = ((uint32)initial_page_dir - KERNEL_START) | PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE;

    invalidate(0xFFFFF000);

    pmm_init(physicalAllocStart, memHigh);

    memset(pageDirs, 0, 0x1000 * NUM_PAGES_DIRS);
    memset(pageDirUsed, 0, NUM_PAGES_DIRS);
}

void invalidate(uint32 vaddr)
{
    asm volatile("invlpg %0" ::"m"(vaddr));
}
