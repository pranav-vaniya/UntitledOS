#include "include/stdio.h"
#include "include/timer.h"
#include "include/vga.h"

void welcome(void)
{
    char *msg = "The fears we don't face, become our limits.\n\t - Robin Sharma\n";

    printf(msg);

    sleep(3000);
    resetVGA();
}
