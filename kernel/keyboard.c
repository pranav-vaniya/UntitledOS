#include "include/stdint.h"
#include "include/util.h"
#include "include/vga.h"
#include "include/idt.h"
#include "include/keyboard.h"

bool capsOn;
bool capsLock;

const uint32 UNKNOWN = 0xFFFFFFFF;
const uint32 ESC = 0xFFFFFFFF - 1;
const uint32 CTRL = 0xFFFFFFFF - 2;
const uint32 LSHFT = 0xFFFFFFFF - 3;
const uint32 RSHFT = 0xFFFFFFFF - 4;
const uint32 ALT = 0xFFFFFFFF - 5;
const uint32 F1 = 0xFFFFFFFF - 6;
const uint32 F2 = 0xFFFFFFFF - 7;
const uint32 F3 = 0xFFFFFFFF - 8;
const uint32 F4 = 0xFFFFFFFF - 9;
const uint32 F5 = 0xFFFFFFFF - 10;
const uint32 F6 = 0xFFFFFFFF - 11;
const uint32 F7 = 0xFFFFFFFF - 12;
const uint32 F8 = 0xFFFFFFFF - 13;
const uint32 F9 = 0xFFFFFFFF - 14;
const uint32 F10 = 0xFFFFFFFF - 15;
const uint32 F11 = 0xFFFFFFFF - 16;
const uint32 F12 = 0xFFFFFFFF - 17;
const uint32 SCRLCK = 0xFFFFFFFF - 18;
const uint32 HOME = 0xFFFFFFFF - 19;
const uint32 UP = 0xFFFFFFFF - 20;
const uint32 LEFT = 0xFFFFFFFF - 21;
const uint32 RIGHT = 0xFFFFFFFF - 22;
const uint32 DOWN = 0xFFFFFFFF - 23;
const uint32 PGUP = 0xFFFFFFFF - 24;
const uint32 PGDOWN = 0xFFFFFFFF - 25;
const uint32 END = 0xFFFFFFFF - 26;
const uint32 INS = 0xFFFFFFFF - 27;
const uint32 DEL = 0xFFFFFFFF - 28;
const uint32 CAPS = 0xFFFFFFFF - 29;
const uint32 NONE = 0xFFFFFFFF - 30;
const uint32 ALTGR = 0xFFFFFFFF - 31;
const uint32 NUMLCK = 0xFFFFFFFF - 32;

const uint32 lowercase[128] = {
    UNKNOWN, ESC, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', CTRL,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', LSHFT, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',',
    '.', '/', RSHFT, '*', ALT, ' ', CAPS, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, NUMLCK, SCRLCK, HOME, UP, PGUP, '-', LEFT, UNKNOWN, RIGHT,
    '+', END, DOWN, PGDOWN, INS, DEL, UNKNOWN, UNKNOWN, UNKNOWN, F11, F12, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN};

const uint32 uppercase[128] = {
    UNKNOWN, ESC, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R',
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', CTRL, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', LSHFT, '|', 'Z', 'X', 'C',
    'V', 'B', 'N', 'M', '<', '>', '?', RSHFT, '*', ALT, ' ', CAPS, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, NUMLCK, SCRLCK, HOME, UP, PGUP, '-',
    LEFT, UNKNOWN, RIGHT, '+', END, DOWN, PGDOWN, INS, DEL, UNKNOWN, UNKNOWN, UNKNOWN, F11, F12, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN};

void keyboardHandler(struct InterruptRegisters *regs)
{
    char scanCode = inPortB(0x60) & 0x7F; // What key is pressed
    char press = inPortB(0x60) & 0x80;    // Press down, or released

    switch (scanCode)
    {
    case 1:
    case 29:
    case 56:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 87:
    case 88:
        break;
        
    case 42:
        // shift key
        if (press == 0)
        {
            capsOn = true;
        }
        else
        {
            capsOn = false;
        }
        break;

    case 58:
        if (!capsLock && press == 0)
        {
            capsLock = true;
        }
        else if (capsLock && press == 0)
        {
            capsLock = false;
        }
        break;

    default:
        if (press == 0)
        {
            if (capsOn || capsLock)
            {
                putc(uppercase[scanCode]);
            }
            else
            {
                putc(lowercase[scanCode]);
            }
        }
    }
}

void initKeyboard()
{
    capsOn = false;
    capsLock = false;
    irq_install_handler(1, &keyboardHandler);
}
