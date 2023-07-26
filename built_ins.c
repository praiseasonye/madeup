#include "main.h"

/**
 * shell_exit - built in command to exit the shell.
 *
 * @argv: Array of arguments passed to the exit command
 *
 * Return: void
 *
 */

void shell_exit(char **argv)
{
	int exit_status = 0;

	if (argv[1] != NULL)
	{
		exit_status = atoi(argv[1]);
	}

	exit(exit_status);
}

/**
 * shell_env - a builtin function that prints the system
 *             environment in the shell terminal
 * @argv: the command line arguments.
 *
 * Return: void
 */

void shell_env(char __attribute__((unused))**argv)
{
	char **env = environ;
	int i = 0, j = 0;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; env[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
