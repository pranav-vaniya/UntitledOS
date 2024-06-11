#pragma once

#include "util.h"

void initTimer();
void onTrq0(struct InterruptRegisters *regs);
uint64 time();
void sleep(uint64 milliseconds);
