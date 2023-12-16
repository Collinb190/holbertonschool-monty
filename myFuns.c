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
 *
 * Descripton: parses the monty file to get commands
*/
char **tokenArry = NULL;
void parseMD(FILE *montyDoc, instruction_t instruction[])
{
	int i;
	unsigned int line_number = 1;
	stack_t *stack = NULL;
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
		tokenArry = tokenize(line);
		for (i = 0; instruction[i].opcode != NULL; i++)
		{
			if (tokenArry[0] == NULL)
			{
				freeTokenArry(tokenArry);
				break;
			}
			if (strcmp(tokenArry[0], instruction[i].opcode) == 0)
			{
				instruction[i].f(&stack, line_number);
				freeTokenArry(tokenArry);
				break;
			}
		}
		if (instruction[i].opcode == NULL)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", line_number, tokenArry[0]);
			freeTokenArry(tokenArry);
			exit(EXIT_FAILURE);
		}
		line_number++;
	}
	free(line);
	freeTokenArry(tokenArry);
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
	char **tokenArry;
	char *token;
	int tokenCount;

	tokenArry = malloc(MAX_TOKEN * sizeof(char *));
	if (tokenArry == NULL)
	{
		perror("Malloc failed");
		free(tokenArry);
		exit(EXIT_FAILURE);
	}
	tokenCount = 0;
	token = strtok(line, " \t\n");

	while (token != NULL)
	{
		tokenArry[tokenCount] = strdup(token);
		if (tokenArry[tokenCount] == NULL)
		{
			perror("strdup failed");
			freeTokenArry(tokenArry);
			exit(EXIT_FAILURE);
		}
		tokenCount++;
		if (tokenCount >= MAX_TOKEN)
		{
			perror("to many tokens");
			freeTokenArry(tokenArry);
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " \t");
	}
	tokenArry[tokenCount] = NULL;
	return (tokenArry);
}
/**
 * freeTokenArry - frees each value of the array
 * @tokenArry: array to be freed
 *
 * Descripton - frees each value of the array and then the array
*/
void freeTokenArry(char **tokenArry)
{
	int i;
	for (i = 0; tokenArry[i] != NULL; i++)
	{
		free(tokenArry[i]);
	}
	free(tokenArry);
}