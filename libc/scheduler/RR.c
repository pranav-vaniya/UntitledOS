#include <stdio.h>
#include <process.h>

int time_rr = 0;

struct Process updateProcess(struct Process process, int time_slice)
{
    for (int j = 0; j < time_slice; j++)
    {
        process.progress += 1;
        time_rr++;

        if (process.progress == 100)
        {
            process.endTime = time_rr;
            break;
        }
    }

    return process;
}

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

            if (process[i].progress < 100)
            {
                process[i] = updateProcess(process[i], time_slice);

                if (process[i].progress == 100)
                {
                    completed++;
                }
            }
        }
    }
}