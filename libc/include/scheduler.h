#ifndef _SCHEDULER_H
#define _SCHEDULER_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

void FCFS(struct Process process[], int total);
void RR(struct Process process[], int total, int time_slice);
void HPF(struct Process process[], int total);
void NDF(struct Process process[], int total);

#ifdef __cplusplus
}
#endif

#endif
