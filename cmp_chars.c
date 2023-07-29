#include "main.h"

/**
 * cmp_chars - compare chars of strings
 *
 * @str: input string.
 *
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */

int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}
