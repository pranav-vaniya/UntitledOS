#include "include/stdint.h"

void strcat(char *dest, char *src)
{
    while (*dest)
    {
        dest++;
    }

    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
}

void charcat(char *str, char c)
{
    int i = 0;

    while (str[i] != '\0')
    {
        i++;
    }

    str[i] = c;

    str[i + 1] = '\0';
}

bool isStrEmpty(const char *str)
{
    if (str[0] == '\0')
    {
        return true;
    }

    return false;
}

void remove_last_char(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        i++;
    }

    if (i > 0)
    {
        str[i - 1] = '\0';
    }
}

bool strcmp(char *str1, char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
        {
            return false;
        }
        str1++;
        str2++;
    }

    return (*str1 == '\0' && *str2 == '\0');
}