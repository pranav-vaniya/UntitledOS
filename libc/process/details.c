#include <stdio.h>
#include <process.h>

/**
 * @brief Print details about a process
 * 
 * @param process an object of Process struct
*/
void details(struct Process process){
    printf("Id: %d, ", process.id);
    printf("Pri: %d, ", process.priority);
    printf("Sts: %d, ", process.status);
    printf("DL: %d, ", process.deadline);
    printf("BT: %d, ", process.burstTime);
    printf("ST: %d, ", process.startTime);
    printf("ET: %d\n", process.endTime);
}
