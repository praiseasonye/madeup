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
	char *cmd = NULL;
	int exec_return;
	pid_t child_pid;
	int status; size_t i;
	builtin_command builtins[] = {
		{"exit", shell_exit},
		{NULL, NULL}
	};

	if (argv)
	{
		/* check if the command is a built-in command*/
		for (i = 0; builtins[i].name != NULL; i++)
		{
			if (_strcmp(argv[0], builtins[i].name) == 0)
			{
				builtins[i].func(argv);
				return;
			}
		}
		/* then it's a system command */
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("fork process failed");
			return;
		}
		else if (child_pid == 0)
		{
			cmd = get_cmddir(argv[0]);
			if (cmd == NULL)
			{
				perror("Command not found");
				exit(EXIT_FAILURE);
			}
			exec_return = execve(cmd, argv, NULL);
			if (exec_return == -1)
			{
				perror("NOT FOUND: No such file or directory");
				exit(EXIT_FAILURE);
			}
		}

		else
			waitpid(child_pid, &status, 0);
	}

}
