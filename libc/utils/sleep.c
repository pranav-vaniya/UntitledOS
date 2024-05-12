#include <stdio.h>

/**
 * @brief Eat 5-Star. Do Nothing.
 * 
 * @param n A Multiplier
*/
void sleep(int n)
{
    for (int i = 0; i < 50000000 * n; i++)
    {
        /* Eat 5-Star. Do Nothing. */
        printf("");
        /* Doing Nothing won't work unless you do something, because of compiler optimizations. */
    }
}
