#include "stack.h"

static int stack[MAX_STACK_SIZE] = {0};
static int sp = 0;

int push(int value) {
  int status = SUCCESS;

  if (sp >= MAX_STACK_SIZE) {
    status = ERR_Stack_Overflow;
  } else {
    stack[sp] = value;
    sp = (sp + 1);
  }
  return status;
}

int pop(int *value) {
  int status = SUCCESS;

  if (sp <= 0) {
    status = ERR_Stack_Underflow;
  } else {
    sp = (sp - 1);
    *value = stack[sp];
  }
  return status;
}

void clearStack(void) { sp = 0; }

int getStackSize(void) { return sp; }

int getStackElement(int index, int *value) {
  int status = SUCCESS;

  if ((index < 0) || (index >= sp)) {
    status = ERR_Stack_Underflow;
  } else {
    *value = stack[index];
  }

  return status;
}