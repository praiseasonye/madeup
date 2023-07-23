#include "main.h"

/**
 * _strdup - a function that allocates memory and
 *           copys a string to the allocated memory
 * @str: the string to be copied
 *
 * Return: the newly copied string.
 *
 */

char *_strdup(char *str)
{
	size_t len = _strlen(str);
	char *new_str = malloc(len + 1);

	if (new_str != NULL)
	{
		_strcpy(new_str, str);
		new_str[len] = '\0';
	}

	return (new_str);
}

