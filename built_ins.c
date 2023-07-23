#include "main.h"

/**
 * Shell built-in command: exit
 * @argv: Array of arguments passed to the exit command
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
