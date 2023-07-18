#include "main.h"

/**
 * main - entry point of the shell program
 * @argc: this is the number of arguments passed to
 *        the shell
 * @argv: these are the arguments in strings passed to
 *        shell.
 * Return: 0 if successful
 *
 */

int main(int argc, char **argv)
{
	char *prompt = "($) ";
	char *inputptr;
	size_t n = 0;
	
	(void)argc; (void)argv;

	/* The prompt that would be displayed
	 * whenever the shell is launched */
	write(STDOUT_FILENO, prompt, 4);
	
	/*getline function to get the shell commandline
	 * arguments inputed by the user*/
	getline(&inputptr, &n, stdin);

	free(inputptr);
	return (0);
}
