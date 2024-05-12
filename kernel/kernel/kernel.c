#include <stdio.h>
#include <process.h>
#include <scheduler.h>
#include <random.h>

#include <kernel/tty.h>

void kernel_main(void)
{
	terminal_initialize();

	printf("Kernel Started!\n\n");

	int process_count = 8;
	struct Process process[process_count];

	for (int i = 0; i < process_count; i++)
	{
		process[i].id = i + 1;
		process[i].priority = randInt(0, 10);
		process[i].status = 0;
		process[i].deadline = randInt(200, 850);
		process[i].burstTime = randInt(50, 100);
		process[i].startTime = -1;
		process[i].endTime = -1;
		details(process[i]);
	}
	printf("\n");

	// FCFS(process, process_count);
	// RR(process, process_count, 4);
	// HPF(process, process_count);
	NDF(process, process_count);
	
	for (int i = 0; i < process_count; i++)
	{
		details(process[i]);
	}

	printf("\nBye, From Kernel. All Defined tasks have been successfully completed.");
}
