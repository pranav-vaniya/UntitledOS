#include "include/vga.h"
#include "include/stdint.h"

uint16 column = 0, line = 0;
uint16 *const vga = (uint16 *const)0xC00B8000;
const uint16 defaultColor = (COLOR_LIGHT_GREY << 8) | (COLOR_BLACK << 12);
uint16 currentColor = defaultColor;

void outb(uint16 port, uint8 val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void move_cursor(int row, int col) {
    uint16 pos = row * 80 + col;

    outb(0x3D4, 14);
    outb(0x3D5, (pos >> 8) & 0xFF);

    outb(0x3D4, 15);
    outb(0x3D5, pos & 0xFF);
}

void ResetVGA()
{
    line = 0;
    column = 0;
    currentColor = defaultColor;

    for (uint16 y = 0; y < height; y++)
    {
        for (uint16 x = 0; x < width; x++)
        {
            vga[y * width + x] = ' ' | defaultColor;
        }
    }
}

void newLine()
{
    if (line < height - 1)
    {
        line++;
        column = 0;
    }
    else
    {
        scrollUp();
        column = 0;
    }
}

void scrollUp()
{
    for (uint16 y = 0; y < height; y++)
    {
        for (uint16 x = 0; x < width; x++)
        {
            vga[(y - 1) * width + x] = vga[y * width + x];
        }
    }

    for (uint16 x = 0; x < width; x++)
    {
        vga[(height - 1) * width + x] = ' ' | currentColor;
    }
}

void print(const char *s)
{
    while (*s)
    {
        switch (*s)
        {
        case '\n':
            newLine();
            break;

        case '\b':
            if (column == 0 && line == 0)
            {
                break;
            }

            if (column == 0 && line != 0)
            {
                line--;
                column = width;
            }
            vga[line * width + (--column)] = ' ' | currentColor;
            break;

        case '\r':
            column = 0;
            break;

        case '\t':
            if (column == width)
            {
                newLine();
            }
            uint16 tabLen = 4 - (column % 4);
            while (tabLen != 0)
            {
                vga[line * width + (column++)] = ' ' | currentColor;
                tabLen--;
            }
            break;

        default:
            if (column == width)
            {
                newLine();
            }

            vga[line * width + (column++)] = *s | currentColor;
            break;
        }

        s++;
    }

    move_cursor(line, column);
}
