#include <stdio.h>
#include <process.h>
#include <stdlib.h>

int time_ndf = 0;

/**
 * @brief Nearest Deadline First Scheduler
 * 
 * @param process[] A list of processes
 * @param total Total number of processes in the list
 */
void NDF(struct Process process[], int total)
{
    int deadlines[total], sorted_dl_indexes[total], i = 0, deadline_fails = 0;

    for (i = 0; i < total; i++)
    {
        deadlines[i] = process[i].deadline;
    }

    genSortedIndexes(deadlines, sorted_dl_indexes, total);

    for (int i = 0; i < total; i++)
    {
        process[sorted_dl_indexes[i]].startTime = time_ndf;

        while (process[sorted_dl_indexes[i]].burstTime > 0)
        {
            process[sorted_dl_indexes[i]].burstTime -= 1;
            time_ndf++;
        }

        process[sorted_dl_indexes[i]].endTime = time_ndf;
        process[sorted_dl_indexes[i]].status = 1;

        if (process[sorted_dl_indexes[i]].endTime > process[sorted_dl_indexes[i]].deadline)
        {
            deadline_fails++;
        }
    }

    printf("There were %d deadline failures.\n\n", deadline_fails);

    time_ndf = 0;
}
