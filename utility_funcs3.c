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
	perror(": ");
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
void print_str(char *str)
{
	int i;

	if (str == NULL)
		str = "(null)";
	for (i = 0; str[i] != '\0'; i++)
		write(STDOUT_FILENO, &str[i], 1);
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
