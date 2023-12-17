#include "monty.h"
/**
 * openMontyFile - opens monty file.
 * @argc: number of arguments.
 * @argv: array of arguments.
 *
 * Description: Checks if the program is called correctly and
 * checks to see if the file is available to us.
 * Return: returns a pointer to the file structure.
*/
FILE *openMontyFile(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	FILE *doc = fopen(argv[1], "r");

	if (!doc)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	return (doc);
}
/**
 * parseMD - parses the monty file
 * @montyDoc: the doc to operate on
 * @instruction[]: the set of opcodes
 *
 * Descripton: parses the monty file to get commands
*/
char **tokenAry = NULL;
stack_t *stack = NULL;
void parseMD(FILE *montyDoc, instruction_t instruction[])
{
	int i;
	unsigned int line_number = 1;
	char *line = NULL;
	size_t len = 0;
	ssize_t charsRead;

	while ((charsRead = getline(&line, &len, montyDoc)) != -1)
	{
		if (charsRead == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		tokenAry = tokenize(line);
		for (i = 0; instruction[i].opcode != NULL; i++)
		{
			if (tokenAry[0] == NULL)
			{
				freeTokenArry(tokenAry);
				break;
			}
			if (strcmp(tokenAry[0], instruction[i].opcode) == 0)
			{
				instruction[i].f(&stack, line_number);
				freeTokenArry(tokenAry);
				break;
			}
		}
		if (instruction[i].opcode == NULL)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, tokenAry[0]);
			freeTokenArry(tokenAry);
			exit(EXIT_FAILURE);
		}
		line_number++;
	}
	free(line);
}
/**
 * tokenize - tokenizes the current line
 * @line: line is current line of monty doc
 *
 * Description: tokenizes the line in the line variable
 * Return: returns an array containg a tokenized line
*/
char **tokenize(char *line)
{
	char **tokenAry;
	char *token;
	int tokenCount;

	tokenAry = malloc(MAX_TOKEN * sizeof(char *));
	if (tokenAry == NULL)
	{
		perror("Malloc failed");
		free(tokenAry);
		exit(EXIT_FAILURE);
	}
	tokenCount = 0;
	token = strtok(line, " \t\n");

	while (token != NULL)
	{
		tokenAry[tokenCount] = strdup(token);
		if (tokenAry[tokenCount] == NULL)
		{
			perror("strdup failed");
			freeTokenArry(tokenAry);
			exit(EXIT_FAILURE);
		}
		tokenCount++;
		if (tokenCount >= MAX_TOKEN)
		{
			perror("to many tokens");
			freeTokenArry(tokenAry);
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " \t");
	}
	tokenAry[tokenCount] = NULL;
	return (tokenAry);
}
/**
 * freeTokenArry - frees each value of the array
 * @tokenAry: array to be freed
 *
 * Descripton - frees each value of the array and then the array
*/
void freeTokenArry(char **tokenAry)
{
	int i;

	for (i = 0; tokenAry[i] != NULL; i++)
	{
		free(tokenAry[i]);
	}
	free(tokenAry);
}
/**
 * freeStack- frees each value of the stack
 * @stack: stack to be freed
 *
 * Descripton - frees each value of the stack and then the stack
*/
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
