#include "main.h"

/**
 * populateenvlist - populates env linked list
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 *
 * Return: Always 0
 */

int populateenvlist(Shell  *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addnodeend(&node, environ[i], 0);
	info->env = node;
	return (0);
}
