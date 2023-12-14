#include "monty.h"

/**
 * handleError - Prints appropriate error messages determined by their error code.
 * @errorCode: The error codes are the following:
 * (1) => The user does not give any file or more than one file to the program.
 * (2) => The file provided is not a file that can be opened or read.
 * (3) => The file provided contains an invalid instruction.
 * (4) => When the program is unable to malloc more memory.
 * (5) => When the parameter passed to the instruction "push" is not an int.
 * (6) => When the stack is empty for pint.
 * (7) => When the stack is empty for pop.
 * (8) => When the stack is too short for the operation.
 */
void handleError(int errorCode, ...)
{
    va_list args;
    char *op;
    int lineNum;

    va_start(args, errorCode);
    switch (errorCode)
    {
        case 1:
            fprintf(stderr, "USAGE: monty file\n");
            break;
        case 2:
            fprintf(stderr, "Error: Can't open file %s\n", va_arg(args, char *));
            break;
        case 3:
            lineNum = va_arg(args, int);
            op = va_arg(args, char *);
            fprintf(stderr, "L%d: unknown instruction %s\n", lineNum, op);
            break;
        case 4:
            fprintf(stderr, "Error: malloc failed\n");
            break;
        case 5:
            fprintf(stderr, "L%d: usage: push integer\n", va_arg(args, int));
            break;
        default:
            break;
    }
    free_nodes();
    exit(EXIT_FAILURE);
}

/**
 * handleMoreError - Handles additional errors.
 * @errorCode: The error codes are the following:
 * (6) => When the stack is empty for pint.
 * (7) => When the stack is empty for pop.
 * (8) => When the stack is too short for the operation.
 * (9) => Division by zero.
 */
void handleMoreError(int errorCode, ...)
{
    va_list args;
    char *op;
    int lineNum;

    va_start(args, errorCode);
    switch (errorCode)
    {
        case 6:
            fprintf(stderr, "L%d: can't pint, stack empty\n", va_arg(args, int));
            break;
        case 7:
            fprintf(stderr, "L%d: can't pop an empty stack\n", va_arg(args, int));
            break;
        case 8:
            lineNum = va_arg(args, unsigned int);
            op = va_arg(args, char *);
            fprintf(stderr, "L%d: can't %s, stack too short\n", lineNum, op);
            break;
        case 9:
            fprintf(stderr, "L%d: division by zero\n", va_arg(args, unsigned int));
            break;
        default:
            break;
    }
    free_nodes();
    exit(EXIT_FAILURE);
}

/**
 * handleStringError - Handles string-related errors.
 * @errorCode: The error codes are the following:
 * (10) ~> The number inside a node is outside ASCII bounds.
 * (11) ~> The stack is empty.
 */
void handleStringError(int errorCode, ...)
{
    va_list args;
    int lineNum;

    va_start(args, errorCode);
    lineNum = va_arg(args, int);
    switch (errorCode)
    {
        case 10:
            fprintf(stderr, "L%d: can't pchar, value out of range\n", lineNum);
            break;
        case 11:
            fprintf(stderr, "L%d: can't pchar, stack empty\n", lineNum);
            break;
        default:
            break;
    }
    free_nodes();
    exit(EXIT_FAILURE);
}

