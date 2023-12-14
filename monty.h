#ifndef MONTY_H
#define MONTY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

/* Data structure representing a node in the stack */
typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

/* Data structure representing an instruction with opcode and function pointer */
typedef struct instruction_s
{
    char *opcode;
    void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* Global variable representing the head of the stack */
extern stack_t *head;
typedef void (*op_func)(stack_t **, unsigned int);

/* Function prototypes for file operations */
void openMontyFile(char *fileName);
int parseMontyLine(char *buffer, int lineNumber, int format);
void readFile(FILE *);
int countChars(FILE *);
void findFunction(char *buffer, char *opcode, int lineNumber, int format);

/* Function prototypes for stack operations */
stack_t *createNode(int value);
void freeNodes(void);
void printStack(stack_t **stack, unsigned int lineNumber);
void addToStack(stack_t **stack, unsigned int lineNumber);
void addToQueue(stack_t **stack, unsigned int lineNumber);
void executeFunction(op_func function, char *opcode, char *buffer, int lineNumber, int format);
void printTop(stack_t **stack, unsigned int lineNumber);
void popTop(stack_t **stack, unsigned int lineNumber);
void noOperation(stack_t **stack, unsigned int lineNumber);
void swapNodes(stack_t **stack, unsigned int lineNumber);

/* Function prototypes for mathematical operations with nodes */
void addNodes(stack_t **stack, unsigned int lineNumber);
void subtractNodes(stack_t **stack, unsigned int lineNumber);
void divideNodes(stack_t **stack, unsigned int lineNumber);
void multiplyNodes(stack_t **stack, unsigned int lineNumber);
void moduloNodes(stack_t **stack, unsigned int lineNumber);

/* Function prototypes for string operations */
void printCharacter(stack_t **stack, unsigned int lineNumber);
void printString(stack_t **stack, unsigned int lineNumber);
void rotateLeft(stack_t **stack, unsigned int lineNumber);
void rotateRight(stack_t **stack, unsigned int lineNumber);

/* Function prototypes for error handling */
void handleError(int errorCode, ...);
void handleAdditionalError(int errorCode, ...);
void handleStringError(int errorCode, ...);

#endif

