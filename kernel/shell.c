#include "include/stdio.h"
#include "include/stdint.h"
#include "include/string.h"
#include "include/shell.h"
#include "include/timer.h"
#include "include/util.h"
#include "include/process.h"
#include "include/scheduler.h"

void printTime();

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
    if (strcmp(command, "time") == 1)
    {
        printTime();
    }

    else if (strcmp(command, "reset") == 1)
    {
        resetProcesses();
    }

    else if (strcmp(command, "fcfs") == 1)
    {
        fcfs();
    }

    else
    {
        printf("\n%s - command not found.\n", command);
    }
}

void printTime()
{
    uint64 current_time = time();
    printf("\n%lld\n", current_time);
}
