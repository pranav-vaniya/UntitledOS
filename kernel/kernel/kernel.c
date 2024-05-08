#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void)
{
	terminal_initialize();

	printf("Hello, From Kernel. The kernel has successfully started.\n\n");

	printf("This OS is Under Construction!");

	printf("\n\nBye, From Kernel. All Defined tasks have been successfully completed.");
}
