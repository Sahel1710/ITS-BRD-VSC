#include "errorhandler.h"
#include "display.h"
#include "scanner.h"
#include "stack.h"
#include "error_codes.h"
#include "token.h"

void handle_error(int errCode) {
    T_token tok;
    tok.tok = 0;
    tok.val = 0;
    
    setErrMode();
    switch(errCode) {
        case ERR_OVERFLOW:
            return printStdout("Error: Overflow detected. Press 'C' to reset.\n");
        case ERR_UNDERFLOW:
            return printStdout("Error: Underflow detected. Press 'C' to reset.\n");
        case ERR_STACK_OVERFLOW:
            return printStdout("Error: Stack overflow. Press 'C' to reset.\n");
        case ERR_STACK_UNDERFLOW:
            return printStdout("Error: Stack underflow. Press 'C' to reset.\n");
        case ERR_DIV_BY_ZERO:
            return printStdout("Error: Division by zero. Press 'C' to reset.\n");
        default:
            return printStdout("Error: Unknown error code. Press 'C' to reset.\n");
    }

    do {
        tok = nextToken();
    } while(tok.tok != CLEAR);

    clearStack();
    clearStdout();
    setNormalMode();

}