#include <stdlib.h>

/**
 * strncpy_ - Copies a string pointed to by @src, and also, by
 * terminating null byte, to a buffer pointed by a @dest.
 *
 * @dest: A buffer I copy to.
 *
 * @src: A source string to cpoy.
 *
 * @n: the amount of characters to copy
 *
 * Return: A pointer to the destination string @dest.
 *
 */

char *strncpy_(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}



/**
 * strncat_ - Concatenates the string pointed to by @src,
 * null byte, to the end of the string pointed to by @dest.
 *
 * @dest: A pointer to the string to be concatenated upon.
 *
 * @src: The source string to be appended to @dest.
 *
 * @n: the amount of bytes
 *
 * Return: A pointer to the destination string @dest.
 *
 */

char *strncat_(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}


/**
 * *strchr_ - locates a character in a  string
 *
 * @s: the string to be parsed
 *
 * @c: the character to look for
 *
 * Return: (s) a pointer to the memory area s
 *
 */

char *strchr_(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * strcmp_ - Compares pointers to two strings.
 * @s1: A pointer to the first string to be compared.
 * @s2: A pointer to the second string to be compared.
 *
 * Return: If str1 < str2, result = the negative difference
 *         If str1 == str2, 0.
 *         If str1 > str2, result = the positive difference
 */

int strcmp_(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
