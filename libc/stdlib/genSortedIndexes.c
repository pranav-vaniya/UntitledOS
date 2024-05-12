#include <stdio.h>

void genSortedIndexes(int arr[], int sorted_index[], int size)
{
    int i, j, min_idx, temp;

    for (i = 0; i < size; i++)
    {
        sorted_index[i] = i;
    }

    for (i = 0; i < size - 1; i++)
    {
        min_idx = i;

        for (j = i + 1; j < size; j++)
        {
            if (arr[sorted_index[j]] < arr[sorted_index[min_idx]])
            {
                min_idx = j;
            }
        }

        temp = sorted_index[min_idx];
        sorted_index[min_idx] = sorted_index[i];
        sorted_index[i] = temp;
    }
}
