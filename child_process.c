#include "main.h"

/**
 * create_child - Creates a child in order to execute another program.
 *
 *
 * @param_array: An array of pointers to strings containing the possible name
 * of a program and its parameters. This array is NULL terminated.
 *
 * @line: The contents of the read line.
 *
 * @count: A counter keeping track of how many commands have been entered
 * into the shell.
 *
 * @av: Name of the program running the shell
 *
 *
 */
void create_child(char **param_array, char *line, int count, char **av)
{
	pid_t id;
	int status;
	int i;
	int check;
	struct stat buf;
	char *tmp_command;
	char *command;

	id = fork();
	if (id == 0)
	{
		tmp_command = param_array[0];
		command = path_finder(param_array[0]);
		if (command == NULL)
		{
			check = stat(tmp_command, &buf);
			if (check == -1)
			{
				error_printing(av[0], count, tmp_command);
				print_str(": not found", 0);
				single_free(2, line, tmp_command);
				for (i = 1; param_array[i]; i++)
					free(param_array[i]);
				free(param_array);
				exit(100);
			}
			command = tmp_command;
		}
		param_array[0] = command;
		if (param_array[0] != NULL)
		{
			if (execve(param_array[0], param_array, environ) == -1)
				exec_error(av[0], count, tmp_command);
		}
	}
	else
		wait(&status);
}

