#include "include/stdint.h"
#include "include/util.h"
#include "include/memory.h"
#include "include/kmalloc.h"

static uint32 heapStart;
static uint32 heapSize;
static uint32 threshold;
static bool kmallocInitialized = false;

void initKmalloc(uint32 initialHeapSize)
{
    heapStart = KERNEL_MALLOC;
    heapSize = 0;
    threshold = 0;
    kmallocInitialized = true;

    changeHeapSize(initialHeapSize);
}

void changeHeapSize(int newSize)
{
    int oldPageTop = CEIL_DIV(heapSize, 0x1000);
    int newPageTop = CEIL_DIV(newSize, 0x1000);

    int diff = newPageTop - oldPageTop;

    for (int i = 0; i < diff; i++)
    {
        uint32 phys = pmmAllocPageFrame();
        memMapPage(KERNEL_MALLOC + oldPageTop * 0x1000 + i * 0x1000, phys, PAGE_FLAG_WRITE);
    }
}
