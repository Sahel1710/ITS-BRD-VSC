#include "rpn.h"
#include "display.h"
#include "error_codes.h"
#include "scanner.h"
#include "stack.h"
#include "token.h"
#include <limits.h>


#define TRUE 1
#define STRING_BUFFER_SIZE 20

static int calcAdd(void);
static int calcSub(void);
static int calcMult(void);
static int calcDiv(void);
static int calcPrintTop(void);
static int calcPrintAll(void);
static int calcClear(void);
static int calcDuplicate(void);
static int calcSwap(void);
static void intToString(int num, char *s);
static int addOverflow(int a, int b);
static int subOverflow(int a, int b);
static int multOverflow(int a, int b);

int runCalculator() {
  T_token currentToken;

    currentToken = nextToken();
    switch (currentToken.tok) {
    case NUMBER:
      return push(currentToken.val);
    case PLUS:
      return calcAdd();
    case MINUS:
      return calcSub();
    case MULT:
      return calcMult();
    case DIV:
      return calcDiv();
    case PRT:
      return calcPrintTop();
    case PRT_ALL:
      return calcPrintAll();
    case CLEAR:
      return calcClear();
    case DOUBLE:
      return calcDuplicate();
    case SWAP:
      return calcSwap();
    default:
      return UNEXPECTED;
    }
  return SUCCESS;
}

static int calcAdd(void) {
  int a = 0;
  int b = 0;
  int status = SUCCESS;

  if ((status = pop(&a)) != SUCCESS) {
    return status;
  }
  if ((status = pop(&b)) != SUCCESS) {
    return status;
  }
  if ((status = addOverflow(a, b)) != SUCCESS) {
    return status;
  }
  return push(b + a);
}

static int calcSub(void) {
  int a = 0;
  int b = 0;
  int status = SUCCESS;

  if ((status = pop(&a)) != SUCCESS) {
    return status;
  }
  if ((status = pop(&b)) != SUCCESS) {
    return status;
  }
  if ((status = subOverflow(a, b)) != SUCCESS) {
    return status;
  }
  return push(b - a);
}

static int calcMult(void) {
  int a = 0;
  int b = 0;
  int status = SUCCESS;

  if ((status = pop(&a)) != SUCCESS) {
    return status;
  }
  if ((status = pop(&b)) != SUCCESS) {
    return status;
  }
  if ((status = multOverflow(a, b)) != SUCCESS) {
    return status;
  }
  return push(b * a);
}

static int calcDiv(void) {
  int divisor = 0;
  int dividend = 0;
  int status = SUCCESS;

  if ((status = pop(&divisor)) != SUCCESS) {
    return status;
  }
  if ((status = pop(&dividend)) != SUCCESS) {
    return status;
  }
  if (divisor == 0) {
    return ERR_DIV_BY_ZERO;
  }
  if ((dividend == INT_MIN) && (divisor == -1)) {
    return ERR_OVERFLOW;
  }
  return push(dividend / divisor);
}

static int addOverflow(int a, int b) {
  if ((a > 0) && (b > (INT_MAX - a))) {
    return ERR_OVERFLOW;
  }

  if ((a < 0) && (b < (INT_MIN - a))) {
    return ERR_UNDERFLOW;
  }
  return SUCCESS;
}

static int subOverflow(int a, int b) {
  if ((b < 0) && (a > (INT_MAX + b))) {
    return ERR_OVERFLOW;
  }
  if ((b > 0) && (a < (INT_MIN + b))) {
    return ERR_UNDERFLOW;
  }
  return SUCCESS;
}

static int multOverflow(int a, int b) {
  if ((a == 0) && (b == 0)) {
    return SUCCESS;
  }
  if ((a > 0) && (b > 0) && (a > (INT_MAX / b))) {
    return ERR_OVERFLOW;
  }
  if ((a < 0) && (b < 0) && (a < (INT_MAX / b))) {
    return ERR_OVERFLOW;
  }
  if ((a > 0) && (b < 0) && (b < (INT_MIN / a))) {
    return ERR_UNDERFLOW;
  }
  if ((a < 0) && (b > 0) && (a < (INT_MIN / b))) {
    return ERR_UNDERFLOW;
  }
  return SUCCESS;
}

static int calcPrintTop(void) {
  int value = 0;
  int status = SUCCESS;
  char buffer[STRING_BUFFER_SIZE] = {0};

  if ((status = getStackElement(getStackSize() - 1, &value)) != SUCCESS) {
    return ERR_STACK_UNDERFLOW;
  }
  intToString(value, buffer);
  printStdout(buffer);
  printStdout("\n");
  return SUCCESS;
}

static int calcPrintAll(void) {
  int value = 0;
  int i = 0;
  int size = 0;
  char buffer[STRING_BUFFER_SIZE] = {0};
  size = getStackSize();

  for (i = (size - 1); i >= 0; i = (i - 1)) {
    if (getStackElement(i, &value) == SUCCESS) {
      intToString(value, buffer);
      printStdout(buffer);
      printStdout("\n");
    }
  }
  return SUCCESS;
}

static int calcClear(void) {
  clearStack();
  clearStdout();
  setNormalMode();
  return SUCCESS;
}

static int calcDuplicate(void) {
  int value = 0;
  int status = SUCCESS;

  if ((status = pop(&value)) != SUCCESS) {
    return status;
  }
  push(value);
  return push(value);
}

static int calcSwap(void) {
  int a = 0;
  int b = 0;
  int status = SUCCESS;

  if ((status = pop(&a)) != SUCCESS) {
    return status;
  }
  if ((status = pop(&b)) != SUCCESS) {
    return status;
  }
  push(a);
  return push(b);
}

static void intToString(int num, char *s) {
  int i = 0;
  int negative = 0;

  if (num == 0) {
    s[i++] = '0';
    s[i] = '\0';
    return;
  }

  if (num < 0) {
    negative = 1;
  }

  while (num != 0) {
    int rem = num % 10;
    if (rem < 0) {
      s[i++] = (char)((-rem) + '0');
    } else {
      s[i++] = (char)(rem + '0');
    }
    num = num / 10;
  }

  if (negative != 0) {
    s[i++] = '-';
  }
  s[i] = '\0';

  int start = 0;
  int end = i - 1;
  while (start < end) {
    char temp = s[start];
    s[start] = s[end];
    s[end] = temp;
    start++;
    --end;
  }
}
