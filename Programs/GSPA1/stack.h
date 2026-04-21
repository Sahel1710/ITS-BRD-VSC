#ifndef STACK_H
#define STACK_H

#include "error_codes.h"

#define MAX_STACK_SIZE 50

int push(int value);

int pop(int *value);

void clearStack(void);

int duplicateTop(void);

int swapTop(void);

#endif // STACK_H