#include "main.h"

/**
 * startswith - checks if needle starts with haystack
 *
 * @haystack: string to search
 *
 * @needle: thr substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *startswith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}



/**
 * strcat_ - concatenates two strings
 *
 * @dest: the destination buffer
 *
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *strcat_(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * strcpy_ - Copies a string pointed to by @src, and also, by
 * terminating null byte, to a buffer pointed by a @dest.
 * @dest: A buffer I copy to.
 * @src: A source string to cpoy.
 *
 * Return: A pointer to the destination string @dest.
 */

char *strcpy_(char *dest, char *src)
{
	int i = 0;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);

}
