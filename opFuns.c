#include "monty.h"
/**
 * push - put an element onto the stack
 * @stack: the stack to be manipulated
 * @line_number: the current line number
 *
 * Descripton: Used to put an element onto the stack
*/
void push(stack_t **stack, unsigned int line_number)
{
	int value;
	stack_t *newNode = NULL;

	if (tokenAry[1] == NULL || !isInt(tokenAry[1]))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	value = atoi(tokenAry[1]);
	newNode = malloc(sizeof(stack_t));
	if (newNode == NULL)
	{
		perror("Malloc failed");
		exit(EXIT_FAILURE);
	}
	newNode->n = value;
	newNode->prev = NULL;
	newNode->next = *stack;
	if (*stack != NULL)
	{
		(*stack)->prev = newNode;
	}
	*stack = newNode;
}
/**
 * pall - prints all elements of the stack
 * @stack: the stack to be manipulated
 * @line_number: the current line number
 *
 * Descripton: Used to print all elements of the stack
*/
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = NULL;
	(void)line_number;

	current = *stack;
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
void freeStack(stack_t *stack)
{
	stack_t *current = stack;
	stack_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
