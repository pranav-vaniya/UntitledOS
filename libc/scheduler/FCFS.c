#include <stdio.h>
#include <process.h>

int time_fcfs = 0;

void FCFS(struct Process process[], int total)
{
    for (int i = 0; i < total; i++)
    {
        process[i].startTime = time_fcfs;

        while (process[i].progress < 100)
        {
            process[i].progress += 1;
            time_fcfs++;
        }

        process[i].endTime = time_fcfs;
    }

    time_fcfs = 0;
}