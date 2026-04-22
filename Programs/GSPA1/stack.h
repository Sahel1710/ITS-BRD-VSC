#ifndef STACK_H
#define STACK_H

#include "error_codes.h"

#define MAX_STACK_SIZE 100

int push(int value);

int pop(int *value);

void clearStack(void);

int duplicateTop(void);

int swapTop(void);

int getStackSize(void);

int getStackElement(int index, int *value);

#endif // STACK_H