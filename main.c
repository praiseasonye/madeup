#include "main.h"
#include <stdio.h>

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
	char *prompt = "($) ", *inputptr = NULL;
	const char *delim = " \n";
	size_t n = 0;
	int num_toks;
	ssize_t num_chars_read;

	(void)argc;
	while (1)
	{
		/* The prompt that would be displayed whenever the shell is launched */
		write(STDOUT_FILENO, prompt, 4);
		/*getline function to get the shell commandline*/
		/* arguments inputed by the user*/
		num_chars_read = getline(&inputptr, &n, stdin);
		if (num_chars_read == -1)
		{
			perror("Error reading input");
			break;
		}
		argv = tokenize(inputptr, delim, &num_toks);
		if (argv == NULL)
		{
			perror("Tokenization failed");
			break;
		}
		execute_cmd(argv);
		/*free(inputptr);*/
		double_free(argv);
	}
	return (0);
}
