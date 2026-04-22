#include "errorhandler.h"
#include "display.h"
#include "scanner.h"
#include "stack.h"

void handle_error(int errCode) {
    setErrMode();
    switch(errCode) {
        case ERR_Overflow:
            printStdout("Error: Overflow detected.");
            break;
        case ERR_Underflow:
            printStdout("Error: Underflow detected.");
            break;
        case ERR_Stack_Overflow:
            printStdout("Error: Stack overflow.");
            break;
        case ERR_Stack_Underflow:
            printStdout("Error: Stack underflow.");
            break;
        case ERR_DIV_BY_ZERO:
            printStdout("Error: Division by zero.");
            break;
        default:
            printStdout("Error: Unknown error code.");
    }

    printStdout("Press 'C' to reset.\n");

    T_token tok;
    do {
        tok = nextToken();
    } while(tok.tok != CLEAR);

    clearStack();
    clearStdout();
    setNormalMode();

}