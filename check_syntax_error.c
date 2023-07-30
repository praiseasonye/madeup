#include "main.h"

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 *
 * @input: input string
 *
 * Return: 1 if there is an error. 0 in other case
 *
 */

int check_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, begin, 0);
		return (1);
	}

	i = error_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_error(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
