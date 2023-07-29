#include "main.h" 

/**
 * eputchar - writes the character c to stderr
 *
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errnois set appropriately.
 *
 */

int eputchar(char c)
{
	static int i;
	static char buf[BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= BUFF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUFF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * putsfd - prints an input string
 *
 * @str: the string to be printed
 *
 * @fd: the file descriptor to write to
 *
 * Return: the number of chars put
 */

int putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += putfd(*str++, fd);
	}

	return (i);
}

/**
 * putfd - writes the character c to give fd
 *
 * @c: the character to print
 *
 * @fd: the file descriptor to write to
 *
 * Return: on success 1.
 * On error, -1 is returned and errno is set appropriately.
 *
 */

int putfd(char c, int fd)
{
	static int i;
		static char buf[BUFF_SIZE];

		if (c == BUFF_FLUSH || i >= BUFF_SIZE)
		{
			write(fd, buf, i);
			i = 0;
		}

		if (c != BUFF_FLUSH)
			buf[i++] = c;
		return (1);
}

/**
 * erratoi_ - converts a string to an integer
 *
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 *
 */
int erratoi_(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
		result *= 10;
		result += (s[i] - '0');
		if (result > INT_MAX)
			return (-1);
		}
		else
			return (-1);
		}
	return (result);
}

/**
 * printd - function prints a decimal (integer) number (base 10)
 *
 * @input: the input
 *
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 *
 */

int printd(int input, int fd)
{
	int (*__putchar)(char) = putchar_;
	int i, count = 0;
	unsigned int abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = eputchar;
	if (input < 0)
	{
		abs_ = input;
		__putchar('-');
		count++;
	}
	else
		abs_ = input;
	current = abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

