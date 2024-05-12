#include <stdio.h>
#include <process.h>
#include <stdlib.h>

int time_hpf = 0;

/**
 * Highest Priority First
*/
void HPF(struct Process process[], int total)
{
    /* Least Integral Value shows the Hightest Priority i.e. 0 has highest priority and 10 has the least priority */

    int priorities[total], sorted_pri_indexes[total], i = 0;

    for (i = 0; i < total; i++)
    {
        priorities[i] = process[i].priority;
    }

    genSortedIndexes(priorities, sorted_pri_indexes, total);

    for (int i = 0; i < total; i++)
    {
        process[sorted_pri_indexes[i]].startTime = time_hpf;

        while (process[sorted_pri_indexes[i]].burstTime > 0)
        {
            process[sorted_pri_indexes[i]].burstTime -= 1;
            time_hpf++;
        }

        process[sorted_pri_indexes[i]].endTime = time_hpf;
        process[sorted_pri_indexes[i]].status = 1;
    }

    time_hpf = 0;
}
