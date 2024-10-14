#include "include/stdint.h"
#include "include/stdio.h"
#include "include/timer.h"

#define ARRAY_SIZE 128

int static_arr1[ARRAY_SIZE] = {169, 245, 232, 90, 23, 34, 234, 134, 230, 103, 197, 149, 232, 186, 139, 95, 238, 46, 6, 5, 94, 154, 228, 139, 197, 192, 235, 80, 65, 4, 144, 27, 14, 44, 53, 7, 142, 183, 129, 195, 62, 63, 59, 235, 65, 162, 213, 144, 47, 220, 121, 14, 96, 248, 14, 170, 187, 235, 74, 87, 92, 246, 138, 25, 211, 20, 146, 33, 250, 82, 157, 52, 153, 34, 200, 76, 92, 132, 43, 174, 30, 41, 96, 33, 90, 242, 117, 156, 160, 144, 72, 250, 213, 243, 233, 14, 196, 19, 105, 170, 226, 106, 91, 237, 156, 2, 73, 246, 140, 51, 228, 15, 85, 6, 39, 17, 149, 113, 221, 189, 159, 70, 169, 144, 96, 160, 43, 199};
int static_arr2[ARRAY_SIZE] = {233, 103, 90, 166, 87, 224, 111, 1, 6, 0, 216, 7, 3, 77, 97, 219, 196, 49, 204, 223, 80, 14, 243, 121, 84, 62, 97, 59, 206, 158, 240, 23, 185, 46, 129, 77, 107, 19, 200, 5, 100, 241, 81, 253, 212, 72, 214, 5, 16, 94, 158, 184, 113, 184, 182, 178, 241, 21, 152, 94, 147, 142, 134, 245, 132, 217, 132, 153, 12, 216, 191, 237, 66, 36, 70, 156, 246, 245, 90, 239, 52, 30, 69, 218, 80, 81, 95, 100, 207, 41, 225, 217, 62, 102, 244, 162, 224, 82, 226, 23, 151, 102, 27, 36, 151, 61, 36, 189, 136, 63, 157, 102, 157, 138, 249, 188, 173, 9, 170, 218, 223, 242, 36, 40, 46, 38, 28, 77};
int static_arr3[ARRAY_SIZE] = {105, 101, 124, 216, 131, 11, 83, 83, 220, 16, 17, 170, 241, 64, 38, 88, 16, 105, 159, 11, 203, 172, 195, 30, 88, 57, 212, 137, 64, 8, 216, 24, 165, 213, 185, 79, 126, 247, 213, 231, 217, 42, 69, 167, 130, 219, 173, 56, 205, 112, 76, 149, 128, 60, 117, 21, 195, 240, 205, 251, 187, 21, 13, 172, 9, 107, 132, 92, 17, 108, 64, 228, 83, 14, 7, 33, 182, 224, 45, 221, 251, 80, 218, 179, 160, 212, 93, 34, 155, 53, 212, 58, 215, 74, 125, 117, 12, 254, 21, 241, 102, 166, 135, 126, 105, 239, 165, 33, 243, 197, 117, 132, 205, 252, 62, 247, 10, 0, 249, 157, 30, 250, 180, 126, 201, 205, 29, 81};
int static_arr4[ARRAY_SIZE] = {173, 130, 235, 173, 175, 212, 6, 135, 183, 192, 245, 137, 26, 61, 99, 61, 105, 229, 238, 76, 115, 46, 93, 48, 199, 143, 32, 52, 111, 246, 173, 251, 243, 111, 150, 188, 234, 167, 131, 53, 233, 122, 10, 101, 90, 37, 35, 188, 208, 50, 72, 92, 245, 117, 141, 232, 123, 114, 52, 233, 80, 183, 62, 98, 184, 29, 211, 84, 40, 234, 121, 99, 60, 88, 11, 124, 154, 154, 146, 9, 108, 10, 117, 75, 58, 174, 167, 106, 113, 247, 186, 81, 240, 240, 101, 178, 165, 128, 145, 203, 151, 223, 151, 39, 251, 31, 229, 176, 42, 239, 179, 39, 129, 90, 202, 179, 166, 204, 196, 83, 48, 66, 22, 26, 187, 4, 112, 9};

int arr1[ARRAY_SIZE], arr2[ARRAY_SIZE], arr3[ARRAY_SIZE], arr4[ARRAY_SIZE];
int stepcounter1, stepcounter2, stepcounter3, stepcounter4;

void resetProcesses()
{
    stepcounter1 = 0, stepcounter2 = 0, stepcounter3 = 0, stepcounter4 = 0;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        arr1[i] = static_arr1[i];
        arr2[i] = static_arr2[i];
        arr3[i] = static_arr3[i];
        arr4[i] = static_arr4[i];
    }

    printf("\nAll processes have been reset\n");
}

bool process1()
{
    int i = 0;
    bool sorted = true;

    for (i = 0; i < ARRAY_SIZE - 1; i++)
    {
        if (arr1[i] > arr1[i + 1])
        {
            sorted = false;
        }
    }

    if (sorted == true)
    {
        return 1;
    }

    int min_index = stepcounter1, min_value = arr1[min_index], temp;

    for (i = min_index + 1; i < ARRAY_SIZE; i++)
    {
        if (arr1[i] < min_value)
        {
            min_value = arr1[i];
            min_index = i;
        }
    }

    temp = arr1[stepcounter1];
    arr1[stepcounter1] = min_value;
    arr1[min_index] = temp;

    stepcounter1++;

    return 0;
}

bool process2()
{
    int i = 0;
    bool sorted = true;

    for (i = 0; i < ARRAY_SIZE - 1; i++)
    {
        if (arr2[i] > arr2[i + 1])
        {
            sorted = false;
        }
    }

    if (sorted == true)
    {
        return 1;
    }

    int min_index = stepcounter2, min_value = arr2[min_index], temp;

    for (i = min_index + 1; i < ARRAY_SIZE; i++)
    {
        if (arr2[i] < min_value)
        {
            min_value = arr2[i];
            min_index = i;
        }
    }

    temp = arr2[stepcounter2];
    arr2[stepcounter2] = min_value;
    arr2[min_index] = temp;

    stepcounter2++;

    return 0;
}

bool process3()
{
    int i = 0;
    bool sorted = true;

    for (i = 0; i < ARRAY_SIZE - 1; i++)
    {
        if (arr3[i] > arr3[i + 1])
        {
            sorted = false;
        }
    }

    if (sorted == true)
    {
        return 1;
    }

    int min_index = stepcounter3, min_value = arr3[min_index], temp;

    for (i = min_index + 1; i < ARRAY_SIZE; i++)
    {
        if (arr3[i] < min_value)
        {
            min_value = arr3[i];
            min_index = i;
        }
    }

    temp = arr3[stepcounter3];
    arr3[stepcounter3] = min_value;
    arr3[min_index] = temp;

    stepcounter3++;

    return 0;
}

bool process4()
{
    int i = 0;
    bool sorted = true;

    for (i = 0; i < ARRAY_SIZE - 1; i++)
    {
        if (arr4[i] > arr4[i + 1])
        {
            sorted = false;
        }
    }

    if (sorted == true)
    {
        return 1;
    }

    int min_index = stepcounter4, min_value = arr4[min_index], temp;

    for (i = min_index + 1; i < ARRAY_SIZE; i++)
    {
        if (arr4[i] < min_value)
        {
            min_value = arr4[i];
            min_index = i;
        }
    }

    temp = arr4[stepcounter4];
    arr4[stepcounter4] = min_value;
    arr4[min_index] = temp;

    stepcounter4++;

    return 0;
}
