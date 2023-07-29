#include "main.h"

/**
 * free_line_list - frees a line_list
 *
 * @head: head of the linked list.
 *
 * Return: no return.
 *
 */

void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

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
