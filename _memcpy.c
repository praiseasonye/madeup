#include "main.h"

/**
 * _memcpy - copies information between void pointers.
 *
 * @newptr: destination pointer.
 *
 * @ptr: source pointer.
 *
 * @size: size of the new pointer.
 *
 * Return: no return.
 */

void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}
