#include "monty.h"

/**
 * monty_main - entry point
 * @argc: arguments count
 * @argv: list of arguments
 * Return: always 0
 */
int monty_main(int argc, char *argv[])
{
	stack_t *head = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	openMontyFile(argv[1], &head);
	freeNodes(&head);
	return (0);
}

/**
 * createNode - Creates a node.
 * @n: Number to go inside the node.
 * Return: Upon success, a pointer to the node. Otherwise, NULL.
 */
stack_t *createNode(int n)
{
	stack_t *node;

	node = malloc(sizeof(stack_t));
	if (node == NULL)
		handleError(4);
	node->next = NULL;
	node->prev = NULL;
	node->n = n;
	return (node);
}

/**
 * freeNodes - Frees nodes in the stack.
 * @stack: Pointer to the head of the stack.
 */
void freeNodes(stack_t **stack)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
		return;

	while (*stack != NULL)
	{
		tmp = *stack;
		*stack = (*stack)->next;
		free(tmp);
	}
}

/**
 * addToQueue - Adds a node to the queue.
 * @newNode: Pointer to the new node.
 * @stack: Pointer to the head of the stack.
 * @ln: line number of the opcode.
 */
void addToQueue
(stack_t **newNode, stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (newNode == NULL || *newNode == NULL)
		exit(EXIT_FAILURE);
	if (*stack == NULL)
	{
		*stack = *newNode;
		return;
	}
	tmp = *stack;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *newNode;
	(*newNode)->prev = tmp;
}

