#include "main.h"

/**
 * myhistory - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int myhistory(Shell *info)
{
	print_list(info->history);

	return (0);
}

/**
 * unsetalias - sets alias to string
 *
 * @info: parameter struct
 *
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 *
 */
int unsetalias(Shell *info, char *str)
{
	char *p, c;
	int ret;

	p = strchr_(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deletenodeatindex(&(info->alias),
							   getnodeindex(info->alias, nodestartswith(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * setalias - sets alias to string
 *
 * @info: parameter struct
 *
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 *
 */
int setalias(Shell *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetalias(info, str));

	unsetalias(info, str);
	return (addnodeend(&(info->alias), str, 0) == NULL);
}

/**
 * myalias - mimics the alias builtin (man alias)
 *
 * @info: Structure containing pitential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int myalias(Shell *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strchr_(info->argv[i], '=');
		if (p)
			setalias(info, info->argv[i]);
		else
			printalias(nodestartswith(info->alias, info->argv[i], '='));
	}

	return (0);
}
