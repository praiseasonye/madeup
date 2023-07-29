#include "main.h"

/**
 * free_rvar_list - frees a r_var list
 *
 * @head: head of the linked list.
 *
 * Return: no return.
 *
 */

void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

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
