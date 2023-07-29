#include "main.h"

/**
 * writehistory - creates a file, or appends to an existing file
 *
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */

int writehistory(Shell  *info)
{
	int fd;
	char *filename = gethistoryfile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		putsfd(node->str, fd);
		putfd('\n', fd);
	}
	putfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * gethistoryfile - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */

char *gethistoryfile(Shell  *info)
{
	char *buf, *dir;

	dir = getenv_(info, "HIME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (strlen_(dir) + strlen_(HISTFILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	strcpy_(buf, dir);
	strcat_(buf, "/");
	strcat_(buf, HIST_FILE);
	return (buf);
}

/**
 * buildhistorylist - adds entry to a history linked list
 *
 * @info: Structure containing potential arguments. Used to maintain
 *
 * @buf: buffer
 *
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildhistorylist(Shell *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	addnodeend(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumberhistory - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumberhistory(ShellInfo  *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

int readhistory(ShellInfo  *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gethistoryfile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			buildhistorylist(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildhistorylist(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		deletenodeatindex(&(info->history), 0);
	renumberhistory(info);
	return (info->histcount);
}
