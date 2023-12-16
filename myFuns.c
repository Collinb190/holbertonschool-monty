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
		fprintf(stderr, "Usage: monty file\n");
		exit(EXIT_FAILURE);
	}
	FILE *doc = fopen(argv[1], "r");

	if (!doc)
	{
		fprintf(stderr, "Error: Can't open %s\n", argv[1]);
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
		tokenArry = tokenize(line); /* first init of tokenArry */

		for (i = 0; instruction[i].opcode != NULL; i++)
		{
			if (strcmp(tokenArry[0], instruction[i].opcode) == 0)
			{
				instruction[i].f(&stack, line_number);
			}
			else
			{
				fprintf(stderr, "L %u: unknown instruction %s", line_number, tokenArry[0]);
				exit(EXIT_FAILURE);
			}
		}
		line_number++;
		free(tokenArry); /* add code to free the array line by line */
		free(line);
	}
}
/**
 * tokenize - tokenizes the current line
 *
 * Description: tokenizes the line in the line variable
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
			exit(EXIT_FAILURE);
		}
		tokenCount++;
		if (tokenCount >= MAX_TOKEN)
		{
			perror("to many tokens");
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " \t");
	}
	tokenArry[tokenCount] = NULL;
	return (tokenArry);
}
