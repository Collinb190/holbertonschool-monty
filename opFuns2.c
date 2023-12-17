#include "monty.h"
/**
 * add - adds togther(fuse) top two elements
 * @stack: stack to manipulate
 * @line_number: current line of monty doc
 *
 * Descripton: Used to add together(fuse) the top two elements on the stack
*/
void add(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n += (*stack)->n;
	pop(stack, line_number);
}
/**
 * nop - does nothing
 * @stack: stack to manipulate
 * @line_number: current line of monty doc
 *
 * Descripton: Used to do nothing to the stack
*/
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
