#include <stdio.h>
#include <process.h>

int time_fcfs = 0;

/**
 * @brief First Come First Serve Scheduler
 * 
 * @param process[] A list of processes
 * @param total Total number of processes in the list
*/
void FCFS(struct Process process[], int total)
{
    for (int i = 0; i < total; i++)
    {
        process[i].startTime = time_fcfs;

        while (process[i].burstTime > 0)
        {
            process[i].burstTime -= 1;
            time_fcfs++;
        }

        process[i].endTime = time_fcfs;
        process[i].status = 1;
    }

    time_fcfs = 0;
}
