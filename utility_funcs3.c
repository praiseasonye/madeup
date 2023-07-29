#include "main.h"

/**
 * strlen_ - Calculates the lenght of a string.
 *
 *
 * @str: String that needs length to be found.
 *
 *
 * Return: Upon success returns the length of a string. otherwise 0.
 */
int strlen_(char *str)
{
	int i;

	if (str == NULL)
		return (0);
	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}

/**
 * atoi_ - converts a string to an integer
 *
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */

int atoi_(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * strdup_ - duplicates a string
 *
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *strdup_(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}



/**
 * putchar_ - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int putchar_(char c)
{
	return (write(1, &c, 1));
}
