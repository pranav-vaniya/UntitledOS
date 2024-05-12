#include <stdio.h>
#include <process.h>

int time_rr = 0;

struct Process updateProcess(struct Process process, int time_slice)
{
    for (int j = 0; j < time_slice; j++)
    {
        process.burstTime -= 1;
        time_rr++;

        if (process.burstTime <= 0)
        {
            process.endTime = time_rr;
            break;
        }
    }

    return process;
}

/**
 * @brief Round Robin Scheduler
 * 
 * @param process[] A list of processes
 * @param total Total number of processes in the list
*/
void RR(struct Process process[], int total, int time_slice)
{
    int completed = 0;

    while (completed != total)
    {
        for (int i = 0; i < total; i++)
        {
            if (process[i].startTime == -1)
            {
                process[i].startTime = time_rr;
            }

            if (process[i].burstTime > 0)
            {
                process[i] = updateProcess(process[i], time_slice);

                if (process[i].burstTime == 0)
                {
                    completed++;
                    process[i].status = 1;
                }
            }
        }
    }
}
