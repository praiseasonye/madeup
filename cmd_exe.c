#include "main.h"

/**
 * execute_cmd - a function that executes a command
 *
 * @argv: the already parsed command line arguments.
 *
 * Return:  void
 *
 */


void execute_cmd(char **argv)
{
	char *first_command = NULL;
	int exec_return;

	if(argv)
	{
		first_command = argv[0];
		exec_return = execve(first_command, argv, NULL);
		if (exec_return == -1)
			write(STDERR_FILENO, "ERROR: No such command\n", 23);
	}
}
