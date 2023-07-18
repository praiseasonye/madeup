#include "main.h"
#include <stdio.h>
#include <string.h>

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
	char *inputptr_copy = NULL;
	const char *delim = " \n";
	size_t n = 0;
	int i;
	char *tokens;
	int num_toks = 0;
	ssize_t num_chars_read;
	
	(void)argc;

	while(1)
	{
		/* The prompt that would be displayed
	 	* whenever the shell is launched */
		write(STDOUT_FILENO, prompt, 4);
	
		/*getline function to get the shell commandline
	 	* arguments inputed by the user*/
		num_chars_read = getline(&inputptr, &n, stdin);
		if (num_chars_read == -1)
		{
			/*free(inputptr);*/
			return (-1);
		}

		inputptr_copy = malloc(sizeof(char) * num_chars_read + 1);
		if (inputptr_copy == NULL)
		{
			write(STDERR_FILENO, "Memory allocation error", 23);
			free(inputptr);
			return (-1);
		}
		_strcpy(inputptr_copy, inputptr);

		tokens = strtok(inputptr, delim);

		while (tokens != NULL)
		{
			num_toks++;
			tokens = strtok(NULL, delim);
		}
		num_toks++;

		/* allocate space and reassign argv to hold the array of strings
		 * each token would be assigned as a command line argument*/

		argv = malloc(sizeof(char *) * num_toks);

		tokens = strtok(inputptr_copy, delim);

		for (i = 0; tokens != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * _strlen(tokens));
			_strcpy(argv[i], tokens);
			tokens = strtok(NULL, delim);
		}
		argv[i] = NULL;

		/* Execute a command via the path to the executabele file*/
		execute_cmd(argv);
		
	}

	free(inputptr);
	free(inputptr_copy);

	return (0);
}
