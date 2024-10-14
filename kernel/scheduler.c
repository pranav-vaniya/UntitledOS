#include "include/scheduler.h"
#include "include/stdint.h"
#include "include/process.h"
#include "include/timer.h"
#include "include/stdio.h"

void fcfs()
{
    printf("\nScheduling set to First Come First Serve\n");

    bool process_status;
    uint64 current_time = time();

    // process 1
    printf("INFO: Process 1 Started\n");

    process_status = process1();
    while (process_status != 1)
    {
        process_status = process1();
    }

    printf("INFO: Process 1 Ended\n");

    // process 2
    printf("INFO: Process 2 Started\n");

    process_status = process2();
    while (process_status != 1)
    {
        process_status = process2();
    }

    printf("INFO: Process 2 Ended\n");

    // process 3
    printf("INFO: Process 3 Started\n");

    process_status = process3();
    while (process_status != 1)
    {
        process_status = process3();
    }

    printf("INFO: Process 3 Ended\n");

    // process 4
    printf("INFO: Process 4 Started\n");

    process_status = process4();
    while (process_status != 1)
    {
        process_status = process4();
    }

    printf("INFO: Process 4 Ended\n");

    printf("All processes completed succesfully.\n");
}
