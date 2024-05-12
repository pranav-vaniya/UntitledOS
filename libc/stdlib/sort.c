#include <stdio.h>

/**
 * @brief Sort an Integer array in ascending order (in-place)
 * 
 * @param arr An array of integers
 * @param size Size of the array
*/
void sort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
