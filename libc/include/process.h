#ifndef _PROCESS_H
#define _PROCESS_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * id, priority, status, burstTime, startTime, endTime
*/
struct Process
{
    int id;
    int priority;
    int status;
    int deadline;
    int burstTime;
    int startTime;
    int endTime;
};

void details(struct Process process);

#ifdef __cplusplus
}
#endif

#endif
