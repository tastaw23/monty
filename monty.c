#include "monty.h"

/* Function prototypes */
void push(stack_t **stack, int value);
void pall(stack_t **stack);

int main(int argc, char *argv[])
{
	/* Check for the correct number of command line arguments */
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	/* Open the file */
	FILE *file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* Stack pointer */
	stack_t *stack = NULL;

	/* Read and process each line of the file */
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 1;

	while ((read = getline(&line, &len, file)) != -1)
	{
		/* Process the line (implement your bytecode execution logic here) */
		process_line(&stack, line, line_number);
		line_number++;
	}

	/* Cleanup and close the file */
	free(line);
	fclose(file);

	/* Free allocated memory for the stack */
	while (stack)
	{
		stack_t *temp = stack;
		stack = stack->next;
		free(temp);
	}

	return 0;
}

/* Function to process each line of the file */
void process_line(stack_t **stack, char *line, unsigned int line_number)
{
	char *opcode, *argument;
	int value;

	/* Tokenize the line to get opcode and argument (if any) */
	opcode = strtok(line, " \t\n");
	if (!opcode || opcode[0] == '#') /* Ignore comments and empty lines */
		return;

	argument = strtok(NULL, " \t\n");

	/* Execute the appropriate opcode based on the instruction */
	if (strcmp(opcode, "push") == 0)
	{
		if (!argument || !is_integer(argument))
		{
			fprintf(stderr, "L%u: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}

		value = atoi(argument);
		push(stack, value);
	}
	else if (strcmp(opcode, "pall") == 0)
	{
		pall(stack);
	}
	else
	{
		fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
		exit(EXIT_FAILURE);
	}
}

/* Function to push an element onto the stack */
void push(stack_t **stack, int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack)
		(*stack)->prev = new_node;

	*stack = new_node;
}

/* Function to print all values on the stack */
void pall(stack_t **stack)
{
	stack_t *current = *stack;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

