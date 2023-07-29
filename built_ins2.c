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
	printlist(info->history);

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
 * printalias - prints an alias string
 *
 * @node: the alias node
 *
 * Return: ALways 0 on success, 1 on error
 */

int printalias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strchr_(node->str, '=');
		for (a = node->str; a <= p; a++)
			putchar_(*a);
		putchar_('\'');
		puts_(p + 1);
		puts_("'\n");
		return (0);
	}
	return (1);
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

	p = strchr_(str, '=');
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


