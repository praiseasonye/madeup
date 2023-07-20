#include "main.h"

/**
 * execute_cmd - a function that executes a shell command
 *
 * @argv: a pointer to a string (the command line argument
 *        to execute
 *
 * Return: void
 *
 */

void execute_cmd(char **argv)
{
	char *cmd;
	int exec_return;

	if (argv)
	{
		cmd = get_cmddir(argv[0]);
		
		exec_return = execve(cmd, argv, NULL);
		if (exec_return == -1)
			write(STDERR_FILENO, "NOT FOUND: No such file or directory\n", 37);
	}
}
