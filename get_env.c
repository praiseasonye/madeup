#include "main.h"

/**
 * _unsetenv - Remove an environment variable
 *
 * @info: Structure containing npotential arguments. used to maintain
 * constant function prototype
 *
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 *
 */

int _unsetenv(Shell *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startswith(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = deletenodeatindex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * get_environ - returns the string array copy of our environ
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 *
 * Return: Always 0
 *
 */

char **get_environ(Shell  *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listtostrings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * setenv_ - Initialize a new environment variable
 * or modify an existing one
 *
 * @info: Structure containing potential arguments. used to maintain
 * constant function prototype
 *
 * @var: the string env var property
 *
 * @value: the string env var value
 * Return: Always 0
 *
 */

int _setenv(Shell *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(strlen_(var) + strlen_(value) + 2);
	if (!buf)
		return (1);
	strcpy_(buf, var);
	strcat_(buf, "=");
	strcat_(buf, value);
	node = info->env;
	while (node)
	{
		p = startswith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addnodeend(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
