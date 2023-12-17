#include "monty.h"
/**
 * main - interprets monty files
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Description: This program interpets monty commands
 * Return: returns a 0 to signal the program finished without isssue.
*/
int main(int argc, char *argv[])
{
	FILE *montyDoc = openMontyFile(argc, argv);
	instruction_t instruction[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{NULL, NULL}
	};
	parseMD(montyDoc, instruction);
	freeStack(stack);
	fclose(montyDoc);
	return (0);
}
