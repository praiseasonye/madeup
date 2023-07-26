#include "main.h"

/**
 * tokenize_path - Separates a string representing paths as an array
 * of strings contining the path directories.
 *
 *
 * @index: Index of the path in the environment variables.
 *
 *
 * @str: string to separate and tokenize.
 *
 *
 * Return: Upon success a NULL terminated array of pointer to strings.
 * Otherwise returns NULL. Note!: Do not forget to free alocated
 * memory on receiving function or when possible.
 */

char **tokenize_path(int index, char *str)
{
	char *env_var;
	int token_count;
	const char *delim = ":\n";
	char **path_tokens;
	int len;

	len = str_len(str);
	token_count = 0;
	/*Moving the pointer len of str plus = sign*/
	env_var = environ[index] + (len + 1);
	path_tokens = token_interface(env_var, delim, token_count);
	if (path_tokens == NULL)
		return (NULL);

	return (path_tokens);
}

/**
 * build_path - Combines two strings one representing the path directory and
 * one representing the command file.
 *
 * @directory: Represents a directory in the path.
 *
 *
 * @command: Represents a file in a directory of the path.
 *
 *
 * Return: Upon success a string representing the full path of a command.
 * Otherwise NULL.
 */


char *build_path(char *directory, char *command)
{
	int i, j;
	int dir_len;
	int command_len;
	int len;
	char *built;

	if (directory == NULL || command == NULL)
		return (NULL);
	dir_len = str_len(directory) + 1;
	command_len = str_len(command) + 1;
	len = dir_len + command_len;

	built = malloc(sizeof(char) * len);
	if (built == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
	{
		for (j = 0; directory[j] != '\0'; j++, i++)
			built[i] = directory[j];
		built[i] = '/';
		i++;
		for (j = 0; command[j] != '\0'; j++, i++)
			built[i] = command[j];
	}
	built[--i] = '\0';
	return (built);
}
