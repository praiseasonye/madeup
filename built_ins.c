#include "main.h"

/**
 * env_b - Prints all the environmental variables in the current shell.
 *
 *
 * @line: A string representing the input from the user.
 *
 */


void env_b(__attribute__((unused))char *line)
{
	int i;
	int j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}


/**
 * cd_b - Changes the current working directory to the parameter passed to cd.
 *
 *
 * if no parameter is passed it will change directory to HOME.
 *
 *
 * @line: A string representing the input from the user.
 *
 */


void cd_b(char *line)
{
	int index;
	int token_count;
	char **param_array;
	const char *delim = "\n\t ";

	token_count = 0;
	param_array = token_interface(line, delim, token_count);
	if (param_array[0] == NULL)
	{
		single_free(2, param_array, line);
		return;
	}
	if (param_array[1] == NULL)
	{
		index = find_path("HOME");
		chdir((environ[index]) + 5);
	}
	else if (_strcmp(param_array[1], "-") == 0)
		print_str(param_array[1], 0);

	else
		chdir(param_array[1]);
	double_free(param_array);
}


/**
 * exit_b - Exits the shell. After freeing allocated resources.
 *
 *
 * @line: A string representing the input from the user.
 *
 */

void exit_b(char *line)
{
	free(line);
	print_str("\n", 1);
	exit(1);
}

/**
 * built_in - Checks for builtin functions.
 *
 * @command: An array of all the arguments passed to the shell.
 *
 * @line: A string representing the input from the user.
 *
 * Return: If function is found 0. Otherwise -1.
 *
 */
int built_in(char **command, char *line)
{
	void (*build)(char *);

	build = builtin_selector(command[0]);
	if (build == NULL)
		return (-1);
	if (_strcmp("exit", command[0]) == 0)
		double_free(command);
	build(line);
	return (0);
}
