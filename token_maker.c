#include "main.h"

/**
 * iscmd - determines if a file is an executable command
 *
 * @info: the info struct
 *
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int iscmd(Shell  *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupchars - duplicates characters
 *
 * @pathstr: the PATH string
 *
 * @start: starting index
 *
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */

char *dupchars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * findpath - finds this cmd in the PATH string
 *
 * @info: the info struct
 *
 * @pathstr: the PATH string
 *
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */

char *findpath(Shell *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((strlen_(cmd) > 2) && startswith(cmd, "./"))
	{
		if (iscmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dupchars(pathstr, curr_pos, i);
			if (!*path)
				strcat_(path, cmd);
			else
			{
				strcat_(path, "/");
				strcat_(path, cmd);
			}
			if (iscmd(info, path))
				return (path);

			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
