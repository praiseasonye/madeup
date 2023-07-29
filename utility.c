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
