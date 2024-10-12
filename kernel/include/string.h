#pragma once

#include "stdint.h"

void strcat(char *dest, char *src);
void charcat(char *str, char c);
bool isStrEmpty(const char *str);
void remove_last_char(char *str);
bool strcmp(char *str1, char *str2);