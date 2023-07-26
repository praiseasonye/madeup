#include "main.h"


/**
 * find_path - Finds the index of an environmental variable.i
 *
 * @str: Environmental variable that needs to be found.
 *
 *
 * Return: Upon success returns the index of the environmental variable.
 *
 *
 * otherwise returns -1.
 */


int find_path(char *str)
{
	int i;
	int len;
	int j;

	len = str_len(str);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (environ[i][j] != str[j])
				break;
		}
		if (j == len && environ[i][j] == '=')
			return (i);
	}
	return (-1);
}


/**
 * search_directories - Looks through directories stored in path_tokens for a
 * specific file. aka commmand.
 *
 * @path_tokens: A pointer to an array of strings representing the different
 * paths contained in the PATH environmental varible.
 *
 * @command: Represents a command. For example ls, echo, pwd, /bin/ls etc.
 *
 *
 * Return: Upon success a string with the upper most directory containing
 * the command file. Otherwise returns NULL.
 */
char *search_directories(char **path_tokens, char *command)
{
	int i, s;
	char *cwd;
	char *buf;
	size_t size;
	struct stat stat_buf;

	buf = NULL;
	size = 0;
	cwd = getcwd(buf, size);
	if (cwd == NULL)
		return (NULL);
	if (command[0] == '/')
		command = command + 1;
	for (i = 0; path_tokens[i] != NULL; i++)
	{
		s = chdir(path_tokens[i]);
		if (s == -1)
		{
			perror("ERROR!");
			return (NULL);
		}
		s = stat(command, &stat_buf);
		if (s == 0)
		{
			chdir(cwd);
			free(cwd);
			return (path_tokens[i]);
		}
	}
	chdir(cwd);
	free(cwd);
	return (NULL);
}


/**
 * path_finder - Acts as an interface for functions that will be able to
 * find the full path of a program.
 *
 *
 * @command: Represents a command. For example ls, echo, pwd, etc.
 *
 * Return: Upon sucess a string with the full path of the program.
 * for example /bin/ls, /bin/echo, etc. Otherwise returns NULL.
 *
 */


char *path_finder(char *command)
{
	char *str = "PATH";
	char *constructed;
	char **path_tokens;
	int index;
	char *directory;

	index = find_path(str);
	path_tokens = tokenize_path(index, str);
	if (path_tokens == NULL)
		return (NULL);

	directory = search_directories(path_tokens, command);
	if (directory == NULL)
	{
		double_free(path_tokens);
		return (NULL);
	}

	constructed = build_path(directory, command);
	if (constructed == NULL)
	{
		double_free(path_tokens);
		return (NULL);
	}

	double_free(path_tokens);

	return (constructed);
}
