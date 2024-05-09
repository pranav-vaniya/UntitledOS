#include <stdio.h>
#include <process.h>

void details(struct Process process){
    printf("Id: %d, ", process.id);
    printf("Pri: %d, ", process.priority);
    printf("Sts: %d, ", process.status);
    printf("Prg: %d, ", process.progress);
    printf("ST: %d, ", process.startTime);
    printf("ET: %d\n", process.endTime);
}