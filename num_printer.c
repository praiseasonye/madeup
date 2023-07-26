#include "main.h"

/**
 * print_digit - Prints an unsigned int
 * @n: unsigned integer to be printed
 * Return: The amount of numbers printed
 */
int print_digit(int n)
{
	int div;
	int len;
	unsigned int num;

	div = 1;
	len = 0;

	num = n;

	for (; num / div > 9; )
		div *= 10;

	for (; div != 0; )
	{
		len += _write_char('0' + num / div);
		num %= div;
		div /= 10;
	}

	return (len);
}