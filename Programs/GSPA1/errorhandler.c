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

    do {
        tok = nextToken();
    } while(tok.tok != CLEAR);

    clearStack();
    clearStdout();
    setNormalMode();

}