#include "LCD_Touch.h"
#include "display.h"
#include "error_codes.h"
#include "errorhandler.h"
#include "init.h"
#include "rpn.h"
#include <stdbool.h>

extern void initDisplay(void);

int main(void) {
  int status;

  initITSboard();
  initDisplay();
  TP_Init(false);

  while (1) {
    status = runCalculator();
    if (status != SUCCESS) {
      handle_error(status);
    }
  }
  return 0;
}
