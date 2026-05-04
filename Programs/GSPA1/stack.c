#include "stack.h"
#include "error_codes.h"

static int stack[MAX_STACK_SIZE] = {0};
static int sp = 0; /* Stackpointer zeigt auf den nächsten freien Platz */

int push(int value) {
  if (sp >= MAX_STACK_SIZE) {
    return ERR_STACK_OVERFLOW;
  }
  stack[sp++] = value;
  return SUCCESS;
}

int pop(int *value) {
  if (sp <= 0) {
    return ERR_STACK_UNDERFLOW;
  }
  *value = stack[--sp];
  return SUCCESS;
}

void clearStack(void) { 
  sp = 0; 
}

int getStackSize(void) { 
  return sp; 
}

int getStackElement(int index, int *value) {
  if ((index < 0) || (index >= sp)) {
    return ERR_STACK_UNDERFLOW;
  }
  *value = stack[index];
  return SUCCESS;
}