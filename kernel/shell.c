#include "include/stdio.h"
#include "include/stdint.h"
#include "include/string.h"
#include "include/shell.h"

char command[128] = "";

void initShell()
{
    printPS1();
}

void printPS1()
{
    printf("\n> ");
}

void updateShellCommand(char c)
{
    switch (c)
    {

    case '\b':
        if (isStrEmpty(command))
        {
            break;
        }

        remove_last_char(command);
        putc(c);
        break;

    case '\n':
        runCommand();

        command[0] = '\0';
        printPS1();
        break;

    case (0xFFFFFFFF - 1): // ESC key
        printf("\n^TERMINATED\n");
        command[0] = '\0';
        printPS1();
        break;

    default:
        putc(c);
        charcat(command, c);
        break;
    }
}

void runCommand()
{
    printf("\n%s\n", command);
}
