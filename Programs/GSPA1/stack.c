#include "stack.h"

#include <limits.h>

static int stack[MAX_STACK_SIZE];
static int sp = 0;

int push(int value) {
    if(sp >= MAX_STACK_SIZE) {
        return ERR_Stack_Overflow;
    }
    stack[sp++] = value;
    return SUCCESS;
}

int pop(int *value) {
    if(sp <= 0) {
        return ERR_Stack_Underflow;
    }
    *value = stack[--sp];
    return SUCCESS;
}

void clearStack(void) {
    sp = 0;
}

