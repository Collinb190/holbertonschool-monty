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

	if (tokenAry[1] == NULL || tokenAry[1][0] == '\0' || !isdigit(tokenAry[1][0]))
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
/**
 * pint - prints the top element
 * @stack: the stack to manipulate
 * @line_number: current line number of monty doc
 *
 * Descripton: Used to print the top element of the stack
*/
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
/**
 * pop - remove top element of the stack
 * @stack: stack to manipulate
 * @line_number: current line of monty doc
 *
 * Descripton: Used to remove the top element of the stack
*/
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	*stack = temp->next;

	if (*stack != NULL)
	{
		(*stack)->prev = NULL;
	}
	free(temp);
}
/**
 * swap - swaps the top elements
 * @stack: stack to manipulate
 * @line_number: current line of monty doc
 *
 * Descripton: Used swap the top elements of the stack
*/
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = (*stack)->next;
	(*stack)->next = temp->next;
	if (temp->next != NULL)
	{
		temp->next->prev = *stack;
	}
	temp->prev = NULL;
	temp->next = *stack;
	(*stack)->prev = temp;
	*stack = temp;
}
