#include "main.h"

/**
 * getenv_ - gets the value of an environ variable
 *
 * @info: Structure containing potential arguments. Used to maintain
 *
 * @name: env var name
 *
 * Return: the value
 */

char *getenv_(Shell *info, const char *name)
{
	list_t *node  = info->env;
	char *p;

	while (node)
	{
		p = startswith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetenv_ - Iniializes a new environment variable,
 * or modify an existing one
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 *
 * Return: Always 0
 *
 */
int mysetenv_(Shell *info)
{
	if (info->argc != 3)
	{
		eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (setenv_(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * myenv_ - prints the current environment
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 *
 * Return: Always 0
 *
 */
int myenv_(Shell *info)
{
	printliststr(info->env);

	return (0);
}

/**
 * myunsetenv_ - Remove an envirinment variable
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: Always 0
 */
int myunsetenv_(Shell *info)
{
	int i;

	if (info->argc == 1)
	{
		eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetenv_(info, info->argv[i]);

	return (0);
}
