#include "main.h"
#include <string.h>

/**
 * get_cmddir - a function that gets the path of the
 *               commamd given to shell.
 *
 * @cmd: the commamnd we need to get its path.
 *
 * Return: 0 if a valid path was found and -1 if
 *         no valid path was found.
 *
 */

char *get_cmddir(char *cmd)
{
	char *dir = NULL, *dir_copy = NULL, *dir_token = NULL, *file_dir = NULL;
	int cmd_len, dir_len;
	struct stat buffer;

	dir = getenv("PATH");
	if (dir)
	{
		/* Duplicate the dirctory path string do that tokenization by
		 * the strtok() function doesn't destroy the main string */
		dir_copy = malloc(sizeof(char) * _strlen(dir));
		if (dir_copy == NULL)
			return (NULL);
		_strcpy(dir_copy, dir);
		/* gwt the length of string that was passed to ythe command
		 * line of our shell */
		cmd_len = _strlen(cmd);
		
		/* breakdown and tokenize the directory path variable to get all the
		 * directories in the path list independently*/
		dir_token = strtok(dir_copy, ":");
		while (dir_token != NULL)
		{
			/* get the length of the tokenized or broken down directory */
			dir_len = _strlen(dir_token);
			file_dir = malloc((cmd_len + dir_len + 3) * sizeof(char));
			if (file_dir == NULL)
			{
				free(dir_copy);
				return (NULL);
			}
			
			_strcpy(file_dir, dir_token);
			_strcat(file_dir, "/");
			_strcat(file_dir, cmd);
			_strcat(file_dir, "\0");

			if (stat(file_dir, &buffer) == 0)
			{
				free(dir_copy);

				return (file_dir);
			}
			else
			{
				free(file_dir);
				dir_token = strtok(NULL, ":");
			}
		}

		free(dir_copy);
		free(file_dir);

		if (stat(cmd, &buffer) == 0)
		{
			return (cmd);
		}
		return (NULL);
	}

	return (NULL);

}
