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
int mem_num_vpages;

void pmm_init(uint32 memLow, uint32 memHigh)
{
    pageFrameMin = CEIL_DIV(memLow, 0x1000);
    pageFrameMax = memHigh / 0x1000;
    totalAlloc = 0;

    memset(physicalMemoryBitmap, 0, sizeof(physicalMemoryBitmap));
}

uint32 pmmAllocPageFrame()
{
    uint32 start = pageFrameMin / 8 + ((pageFrameMin & 7) != 0 ? 1 : 0);
    uint32 end = pageFrameMax / 8 - ((pageFrameMax & 7) != 0 ? 1 : 0);

    for (uint32 b = start; b < end; b++)
    {
        uint8 byte = physicalMemoryBitmap[b];
        if (byte == 0xFF)
        {
            continue;
        }

        for (uint32 i = 0; i < 8; i++)
        {
            bool used = byte >> i & 1;

            if (!used)
            {
                byte ^= (-1 ^ byte) & (1 << i);

                physicalMemoryBitmap[b] = byte;
                totalAlloc++;

                uint32 addr = (b * 8 * i) * 0x1000;

                return addr;
            }
        }
    }

    return 0;
}

uint32 *memGetCurrentPageDir()
{
    uint32 pd;
    asm volatile("MOV %%cr3, %0" : "=r"(pd));
    pd += KERNEL_START;
    return (uint32 *)pd;
}

void memChangePageDir(uint32 *pd)
{
    pd = (uint32 *)(((uint32)pd) - KERNEL_START);
    asm volatile("MOV %0, %%eax \n mov %%eax, %%cr3 \n" ::"m"(pd));
}

void syncPageDirs()
{
    for (int i = 0; i < NUM_PAGES_DIRS; i++)
    {
        if (pageDirUsed[i])
        {
            uint32 *pageDir = pageDirs[i];

            for (int i = 768; i < 1023; i++)
            {
                pageDir[i] = initial_page_dir[i] & ~PAGE_FLAG_OWNER;
            }
        }
    }
}

void memMapPage(uint32 virtualAddr, uint32 physAddr, uint32 flags)
{
    uint32 *prevPageDir = 0;

    if (virtualAddr >= KERNEL_START)
    {
        prevPageDir = memGetCurrentPageDir();

        if (prevPageDir != initial_page_dir)
        {
            memChangePageDir(initial_page_dir);
        }
    }

    uint32 pdIndex = virtualAddr >> 22;
    uint32 ptIndex = virtualAddr >> 12 & 0x3FF;

    uint32 *pageDir = REC_PAGEDIR;
    uint32 *pt = REC_PAGETABLE(pdIndex);

    if (!(pageDir[pdIndex] & PAGE_FLAG_PRESENT))
    {
        uint32 ptAddr = pmmAllocPageFrame();
        pageDir[pdIndex] = ptAddr | PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE | PAGE_FLAG_OWNER | flags;
        invalidate(virtualAddr);

        for (uint32 i = 0; i < 1024; i++)
        {
            pt[i] = 0;
        }
    }

    pt[ptIndex] = physAddr | PAGE_FLAG_PRESENT | flags;
    mem_num_vpages++;
    invalidate(virtualAddr);

    if (prevPageDir != 0)
    {
        syncPageDirs();

        if (prevPageDir != initial_page_dir)
        {
            memChangePageDir(prevPageDir);
        }
    }
}

void initMemory(uint32 memHigh, uint32 physicalAllocStart)
{
    initial_page_dir[0] = 0;
    mem_num_vpages = 0;

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
