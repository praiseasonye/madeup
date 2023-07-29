#include "main.h"


/**
 * isalpha_ - checks for alphabetic character
 *
 * @c: The character to input
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 *
 */

int isalpha_(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * isdelim - checks if character is a delimeter
 *
 * @c: the char to check
 *
 * @delim: the delimeter string
 *
 * Return: 1 if true, 0 if false
 *
 */
int isdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
		{
			return (1);
		}
	return (0);
}

/**
 * interactive - returns true if shell is interactive mode
 *
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 *
 */
int interactive(Shell *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * myhelp - changes the current directory of the process
 *
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 *
 * Return: Always 0
 */
int myhelp(Shell *info)
{
	char **arg_array;

	arg_array = info->argv;
	puts("Contact <praiseikennaasonye@gmail.com> \n");
	if (0)
		puts(*arg_array); /*temp att_unused workaround */
	return (0);
}

/**
 * eputs - prints an input string
 *
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void eputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		eputchar(str[i]);
		i++;
	}
}
