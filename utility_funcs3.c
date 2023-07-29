#include "main.h"

/**
 * exec_error - Prints exec errors.
 *
 * @av: The name of the program running the shell.
 *
 * @count: Keeps track of how many commands have been entered.
 *
 * @tmp_command: The command that filed.
 *
 */

void exec_error(char *av, int count, char *tmp_command)
{
	error_printing(av, count, tmp_command);
	print_str(": ", 1);
	perror("");
	exit(127);
}

/**
 * print_str - Prints a string character by character.
 *
 * @str: String to be printed. If the string is NULL it will print (null)
 *
 * @new_line: If integer is 0 a new line will be printed. Otherwise a new line
 *
 * will not be printed.
 *
 *
 */
void print_str(char *str, int new_line)
{
	int i;

	if (str == NULL)
		str = "(null)";
	for (i = 0; str[i] != '\0'; i++)
		write(STDOUT_FILENO, &str[i], 1);
	if (new_line == 0)
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * _write_char - Writes a character to stdout
 * @c: Character that will be written to stdout
 * Return: Upon success how many characters were written.
 */
int _write_char(char c)
{
	return (write(1, &c, 1));
}

/**
 * str_len - Calculates the lenght of a string.
 *
 *
 * @str: String that needs length to be found.
 *
 *
 * Return: Upon success returns the length of a string. otherwise 0.
 */
int str_len(char *str)
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
