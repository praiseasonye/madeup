#include "main.h"

/**
 * first_char - finds index of the first char
 *
 * @input: input string
 *
 * @i: index
 *
 * Return: 1 if there is an error. 0 in other case.
 */

int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}
