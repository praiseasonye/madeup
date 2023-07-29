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
 * strcmp_ - performs lexicographic comparison of two strings
 *
 * @s1: the first string
 *
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, 0 if s1 == s2
 */
int strcmp_(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);

	else
		return (*s1 < *s2 ? -1 : 1);
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
