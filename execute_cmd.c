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
	pid_t child_pid;
	int status;

	if (argv)
	{
		child_pid = fork();
		if (child_pid < 0)
		{
			write(STDERR_FILENO, "fork process failed", 19);
			return;
		}
		else if (child_pid == 0)
		{
			cmd = get_cmddir(argv[0]);
			if (cmd == NULL)
			{
				write(STDERR_FILENO, "Command not found\n", 18);
				exit(EXIT_FAILURE);
			}
			exec_return = execve(cmd, argv, NULL);
			if (exec_return == -1)
			{
				write(STDERR_FILENO, "NOT FOUND: No such file or directory\n", 37);
				exit(EXIT_FAILURE);
			}
		}

		else
			waitpid(child_pid, &status, 0);
	}

}
