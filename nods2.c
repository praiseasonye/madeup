#include "main.h"

/**
 * listlen - determines length of linked list
 *
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t listlen(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * listtostrings - returns an array of strings of the list->str
 *
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **listtostrings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(strlen_(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = strcpy_(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * printlist - prints all elements of a list_t linked list
 *
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t printlist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		puts_(convert_number(h->num, 10, 0));
		putchar_(':');
		putchar_(' ');
		puts_(h->str ? h->str : "(nil)");
		puts_("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nodestartswith - returns node whose string starts with prefix
 *
 * @node: pointer to list head
 *
 * @prefix: string to match
 *
 * @c: the next xharacter after prefix to matcg
 *
 * Return: match node or null
 */

list_t *nodestartswith(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = start_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getnodeindex - gets the index of a node
 *
 * @head: pointer to list head
 *
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t getnodeindex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
