#include <stdio.h>

/**
 * @brief Generate an array of indexes representing elements of a sorted list
 * 
 * @param arr An Integer array
 * @param sorted_index An array to store the generated array
 * @param size The size of the array
*/
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
