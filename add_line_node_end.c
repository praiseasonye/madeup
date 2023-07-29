#include "main.h"

/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 *
 * @head: head of the linked list.
 *
 * @line: command line.
 *
 * Return: address of the head.
 *
 */

line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}
