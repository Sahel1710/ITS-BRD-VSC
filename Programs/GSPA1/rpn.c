#include "rpn.h"
#include "display.h"
#include "error_codes.h"
#include "errorhandler.h"
#include "scanner.h"
#include "stack.h"
#include "token.h"
#include <limits.h>

static int addOverflow(int a, int b);
static int subOverflow(int a, int b);
static int multOverflow(int a, int b);
static void calcAdd(void);
static void calcSub(void);
static void calcMult(void);
static void calcDiv(void);
static void calcPrintTop(void);
static void calcPrintAll(void);
static void calcClear(void);
static void calcDuplicate(void);
static void calcSwap(void);
static void intToString(int value, char *s);

void runCalculator() {
  T_token currentToken;

  while (1) {
    currentToken = nextToken();
    switch (currentToken.tok) {
    case NUMBER:
      if (push(currentToken.val) != SUCCESS) {
        handle_error(ERR_Stack_Overflow);
      }
      break;
    case PLUS:
      calcAdd();
      break;
    case MINUS:
      calcSub();
      break;
    case MULT:
      calcMult();
      break;
    case DIV:
      calcDiv();
      break;
    case PRT:
      calcPrintTop();
      break;
    case PRT_ALL:
      calcPrintAll();
      break;
    case CLEAR:
      calcClear();
      break;
    case DOUBLE:
      calcDuplicate();
      break;
    case SWAP:
      calcSwap();
      break;
    default:
      break;
    }
  }
}

static void calcAdd(void) {
  int a = 0;
  int b = 0;
  int status = SUCCESS;

  if ((pop(&a) == SUCCESS) && (pop(&b) == SUCCESS)) {
    status = addOverflow(b, a);
    if (status != SUCCESS) {
      handle_error(status);
    } else {
      push(a + b);
    }
  } else {
    handle_error(ERR_Stack_Underflow);
  }
}

static void calcSub(void) {
  int a = 0;
  int b = 0;
  int status = SUCCESS;

  if ((pop(&a) == SUCCESS) && (pop(&b) == SUCCESS)) {
    status = subOverflow(b, a);
    if (status != SUCCESS) {
      handle_error(status);
    } else {
      push(b - a);
    }
  } else {
    handle_error(ERR_Stack_Underflow);
  }
}

static void calcMult(void) {
  int a = 0;
  int b = 0;
  int status = SUCCESS;

  if ((pop(&a) == SUCCESS) && (pop(&b) == SUCCESS)) {
    status = multOverflow(b, a);
    if (status != SUCCESS) {
      handle_error(status);
    } else {
      push(b * a);
    }
  } else {
    handle_error(ERR_Stack_Underflow);
  }
}

static void calcDiv(void) {
  int divisor = 0;
  int dividend = 0;

  if ((pop(&divisor) == SUCCESS) && (pop(&dividend) == SUCCESS)) {
    if (divisor == 0) {
      handle_error(ERR_DIV_BY_ZERO);
    } else if ((dividend == INT_MIN) && (divisor == -1)) {
      handle_error(ERR_Overflow);
    } else {
      push(dividend / divisor);
    }
  } else {
    handle_error(ERR_Stack_Underflow);
  }
}

static int addOverflow(int a, int b) {
  int error = SUCCESS;

  if ((a > 0) && (b > (INT_MAX - a))) {
    error = ERR_Overflow;
  }

  if ((a < 0) && (b < (INT_MIN - a))) {
    error = ERR_Underflow;
  }
  return error;
}

static int subOverflow(int a, int b) {
  int error = SUCCESS;

  if ((b < 0) && (a > (INT_MAX + b))) {
    error = ERR_Overflow;
  }

  if ((b > 0) && (a < (INT_MIN + b))) {
    error = ERR_Underflow;
  }
  return error;
}

static int multOverflow(int a, int b) {
  int error = SUCCESS;

  if ((a != 0) && (b != 0)) {
    if (a > 0) {
      if (b > 0) {
        if (a > (INT_MAX / b)) {
          error = ERR_Overflow;
        }
      } else {
        if (b < (INT_MIN / a)) {
          error = ERR_Underflow;
        }
      }
    } else {
      if (b > 0) {
        if (a < (INT_MIN / b)) {
          error = ERR_Underflow;
        }
      } else {
        if (a < (INT_MAX / b)) {
          error = ERR_Overflow;
        }
      }
    }
  }
  return error;
}

static void calcPrintTop(void) {
  int value = 0;
  char buffer[STRING_BUFFER_SIZE] = {0};

  if (pop(&value) == SUCCESS) {
    intToString(value, buffer);
    printStdout(buffer);
    printStdout("\n");
    push(value);
  } else {
    handle_error(ERR_Stack_Underflow);
  }
}

static void calcPrintAll(void) {
  int value = 0;
  int i = 0;
  int size = 0;
  char buffer[STRING_BUFFER_SIZE] = {0};
  size = getStackSize();

  /* Mit getStackElement lesen wir den Stack zerstörungsfrei von oben nach unten
   */
  for (i = (size - 1); i >= 0; i = (i - 1)) {
    if (getStackElement(i, &value) == SUCCESS) {
      intToString(value, buffer);
      printStdout(buffer);
      printStdout("\n");
    }
  }
}

static void calcClear(void) {
  clearStack();
  clearStdout();
  setNormalMode();
}

static void calcDuplicate(void) {
  int value = 0;
  if (pop(&value) == SUCCESS) {
    push(value);
    if (push(value) != SUCCESS) {
      handle_error(ERR_Stack_Overflow);
    }
  } else {
    handle_error(ERR_Stack_Underflow);
  }
}

static void calcSwap(void) {
  int a = 0;
  int b = 0;

  if ((pop(&a) == SUCCESS) && (pop(&b) == SUCCESS)) {
    push(a);
    push(b);
  } else {
    handle_error(ERR_Stack_Underflow);
  }
}

static void intToString(int value, char *s) {
  int i = 0;
  int negative = 0;
  long num = (long)value;

  if (num == 0) {
    s[i] = '0';
    i = (i + 1);
    s[i] = '\0';
  } else {
    if (num < 0) {
      negative = 1;
      num = -num;
    }
  }

  while (num > 0) {
    s[i] = (int)((num % 10) + '0');
    i = (i + 1);
    num = (num / 10);
  }

  if (negative != 0) {
    s[i] = '-';
    i = (i + 1);
  }
  s[i] = '\0';

  int start = 0;
  int end = i - 1;
  while (start < end) {
    char temp = s[start];
    s[start] = s[end];
    s[end] = temp;
    start = (start + 1);
    end = (end - 1);
  }
}
