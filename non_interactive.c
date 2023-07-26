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
	char buffer[BUFFER_SIZE];
	ssize_t num_chars_read;
	int i, num_toks;
	char **argv = NULL;
	int newline_pos;

	/*Read input from the provided input file descriptor using read */
	while ((num_chars_read = read(input_fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		buffer[num_chars_read] = '\0'; /*Null-terminate the read data */
		/* Check and remove the newline character */
		newline_pos = strcspn(buffer, "\n");
		if (newline_pos != num_chars_read)
			buffer[newline_pos] = '\0';
		/*Tokenize the input into an array of strings */
		argv = tokenize(buffer, " \n", &num_toks);
		if (argv == NULL)
		{
			perror("Tokenization failed");
			break;
		}
		/* Execute the command via the path to the executable file */
		execute_cmd(argv);
		fflush(stdout);
		/*Free dynamically allocated memory for tokens */
		for (i = 0; i < num_toks; i++)
			free(argv[i]);
		free(argv);
	if (num_chars_read == -1)
		perror("Error reading input");
	}
}
