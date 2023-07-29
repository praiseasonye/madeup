#include "main.h"

/**
 * print_error - prints an error message
 *
 * @info: the parameter & return info struct
 *
 * @estr: string containing specified error type
 *
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 *
 */

void printerror(ShellInfo  *info, char *estr)
{
	eputs(info->fname);
	eputs(": ");
	printd(info->line_count, STDERR_FILENO);
	eputs(": ");
	eputs(info->argv[0]);
	eputs(": ");
	eputs(estr);
}

/**
 * convert_number - converter function, a clone of itoa
 *
 * @num: number
 *
 * @base: base
 *
 * @flags: argument flags
 *
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERTUNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERTLOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removecomments - function replaces first instance of '#' with '\0'
 *
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 *
 */

void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
