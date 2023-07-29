#include "main.h"

/**
 * freeinfo - frees ShellInfo  struct fields
 *
 * @info: struct address
 *
 * @all: true if freeing all fields
 *
 */

void freeinfo(Shell  *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freelist(&(info->env));
		if (info->history)
			freelist(&(info->history));
		if (info->alias)
			freelist(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFF_FLUSH);
	}
}


/**
 * setinfo - Initializes ShellInfo  struct
 *
 * @info: struct address
 *
 * @av: argument vector
 *
 */

void setinfo(Shell  *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, "\t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strdup_(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replacealias(info);
		replacevars(info);
	}
}

/**
 * clear_info - Initializes ShellInfo  struct
 * @info: Struct address
 */
void clearinfo(Shell  *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
