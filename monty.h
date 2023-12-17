#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>

#define MAX_TOKEN 64

extern char **tokenAry;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;
extern stack_t *stack;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * openMontyFile - opens monty file.
 * @argc: number of arguments.
 * @argv: array of arguments.
 *
 * Description: Checks if the program is called correctly and
 * checks to see if the file is available to us.
 * Return: returns a pointer to the file structure.
*/
FILE *openMontyFile(int argc, char *argv[]);

/**
 * parseMD - parses the monty file
 *
 * Descripton: parses the monty file to get commands
*/
void parseMD(FILE *montyDoc, instruction_t instruction[]);

/**
 * tokenize - tokenizes the current line
 *
 * Description: tokenizes the line in the line variable
*/
char **tokenize(char *line);

/**
 * freeTokenArry - frees each value of the array
 * @tokenAry: array to be freed
 *
 * Descripton - frees each value of the array and then the array
*/
void freeTokenArry(char **tokenAry);

/**
 * freeStack- frees each value of the stack
 * @stack: stack to be freed
 *
 * Descripton - frees each value of the stack and then the stack
*/
void freeStack(stack_t *stack);

/**
 * push - put an element onto the stack
 * @stack:
 * @line_number: current line of monty doc
 *
 * Descripton: Used to put an element onto the stack
*/
void push(stack_t **stack, unsigned int line_number);

/**
 * pall - prints all elements of the stack
 * @stack:
 * @line_number: current line of monty doc
 *
 * Descripton: Used to print all elements of the stack
*/
void pall(stack_t **stack, unsigned int line_number);

/**
 * pint - prints the top element
 * @stack: the stack to be manipulated
 * @line_number: current line of monty doc
 *
 * Descripton: Used to print the top element of the stack
*/
void pint(stack_t **stack, unsigned int line_number);

/**
 * pop - remove top element of the stack
 * @stack: the stack to be manipulated
 * @line_number: current line of monty doc
 *
 * Descripton: Used to remove the top element of the stack
*/
void pop(stack_t **stack, unsigned int line_number);

/**
 * swap - swaps the top elements
 * @stack: the stack to be manipulated
 * @line_number: current line of monty doc
 *
 * Descripton: Used swap the top elements of the stack
*/
void swap(stack_t **stack, unsigned int line_number);

/**
 * add - adds togther(fuse) top two elements
 * @stack: the stack to be manipulated
 * @line_number: current line of monty doc
 *
 * Descripton: Used to add together(fuse) the top two elements on the stack
*/
void add(stack_t **stack, unsigned int line_number);

/**
 * nop - does nothing
 * @stack: the stack to be manipulated
 * @line_number: current line of monty doc
 *
 * Descripton: Used to do nothing to the stack
*/
void nop(stack_t **stack, unsigned int line_number);

#endif /* MONTY_H */
