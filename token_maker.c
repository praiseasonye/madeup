#include "main.h"
#include <string.h>

/**
 * tokenize - a function that breaks the command line arguments
 *            into an array of strings.
 *
 * @input: the input of the user to the command line.
 * @delim: what would be used to separate the string.
 * @num_tokens: the number of tokens or separate strings
 *              gotten from the input.
 *
 * Return: An array of strings.
 *
 */

char **tokenize(char *input, const char *delim, int *num_tokens)
{
	char *token, *input_copy;
	char **tokens = NULL;
	int count = 0, i;

	input_copy = _strdup(input);
	if (input_copy == NULL)
	{
		perror("Memory allocation error");
		return (NULL);
	}
	token = strtok(input, delim);
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delim);
	}

	if (count > 0)
	{
		tokens = malloc(sizeof(char *) * (count + 1));
		if (tokens != NULL)
		{
			token = strtok(input_copy, delim);
			for (i = 0; i < count; i++)
			{
				tokens[i] = _strdup(token);
				token = strtok(NULL, delim);
			}
			tokens[count] = NULL;
		}
	}

	free(input_copy);
	*num_tokens = count;
	return (tokens);
}
