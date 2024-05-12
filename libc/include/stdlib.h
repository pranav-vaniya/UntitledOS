#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

void sort(int arr[], int size);
void rsort(int arr[], int size);
void genSortedIndexes(int arr[], int sorted_index[], int size);

#ifdef __cplusplus
}
#endif

#endif
