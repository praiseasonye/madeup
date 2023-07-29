#include "main.h"

/**
 * free_sep_list - frees a sep_list
 *
 * @head: head of the linked list.
 *
 * Return: no return.
 */

void free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
