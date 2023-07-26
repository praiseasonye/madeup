#include "main.h"
#include <string.h>

/**
 * handle_non_interactive_mode - handles the non-interactive mode of the
 *                               shell
 * @input_fd: the file descriptor of where the shell is reading commands from
 *
 * Return: void
 */

void handle_non_interactive_mode(int input_fd)
{
	char buffer[BUFFSIZE];
	ssize_t num_chars_read;
	int i, num_toks;
	char **argv = NULL;
	char *command = NULL;

	while ((num_chars_read = read(input_fd, buffer, BUFFSIZE - 1)) > 0)
	{
		buffer[num_chars_read] = '\0'; /* Null-terminate the read data */
		/* Split the input into individual commands using the newline character*/
		command = strtok(buffer, "\n");
		while (command != NULL)
		{
			/* Tokenize each command into arguments */
			argv = tokenize(command, " \n", &num_toks);
			if (argv == NULL)
			{
				perror("Tokenization failed");
				break;
			}
			/* Execute the command via the path to the executable file*/
			execute_cmd(argv);
			fflush(stdout);
			/* Free dynamically allocated memory for tokens */
			for (i = 0; i < num_toks; i++)
				free(argv[i]);
			free(argv);
			/* Move to the next command in the input*/
			command = strtok(NULL, "\n");
		}
		if (num_chars_read == -1)
			perror("Error reading input");
	}
}
