i#include <stdlib.h>
#include <unistd.h>
#include "main.h"
/**
 * _getline - Reads the input
 * @lineptr: Pointer to the buffer
 * @n: Pointer to the size of the buffer
 * Return: number of char read
 */

ssize_t _getline(char **lineptr, size_t *n)
{
	size_t position = 0;/*in the buffer*/
	char store;/*stores the character to be read*/

	if (*lineptr == NULL)/*allocate memory*/
	{	*n = 128;/*random initial buffer size*/
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			write(STDERR_FILENO, "Error:memory alloc failed", 30);
			return (-1);
		}
	}

	while (1)
	{/*create an loops that breaks after reading and returns 1*/
		if (read(STDIN_FILENO, &store, 1) != 1)
		{
			break;
		}

		if (position >= *n - 1)
		{/*if the position is greater than the buffer, double it*/
			size_t new_buffer = *n + 128;
			char *new_lineptr = (char *)malloc(new_buffer);

			if (new_lineptr == NULL)
			{
				write(STDERR_FILENO, "Error: Memory alloc failed\n", 27);
				free(*lineptr);
				*lineptr = NULL;
				return (-1);
			}
			for (size_t i = 0; i < position; i++)
			{
				new_lineptr[i] = (*lineptr)[i];
			}

			free(*lineptr);
			*lineptr = new_lineptr;
			*n = new_buffer;
		}

		(*lineptr)[position++] = store;

		if (store == '\n')
		{
			break;
		}
	}

	(*lineptr)[position] = '\0';
	return (position);
}

