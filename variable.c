#include "main.h"

/**
 * ischain - test if current char in buffer is a chain delimeter
 *
 * @info: the parater struct
 *
 * @buf: the char buffer
 *
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 *
 */

int ischain(Shell *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMDOR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMDAND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0; 
		info->cmd_buf_type = CMDCHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkchain - checks we should continue chaining based on last status
 *
 * @info: the parameter struct
 *
 * @buf: the char buffer
 *
 * @p: address of current position in buf
 *
 * @i: starting position in buf
 *
 * @len: length of buf
 *
 * Return: void
 */

void checkchain(Shell *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMDAND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMDOR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * replacealias - replaces an aliases in the tokenized string
 *
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replacealias(Shell  *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodestartswith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = strchr_(node->str, '=');
		if (!p)
			return (0);
		p = strdup_(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replacevars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replacevars(Shell  *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!strcmp_(info->argv[i], "$?"))
		{
			replacestring(&(info->argv[i]),
				strdup_(convertnumber(info->status, 10, 0)));
			continue;
		}
		if (!strcmp_(info->argv[i], "$$"))
		{
			replacestring(&(info->argv[i]),
					strdup_(convertnumber(getpid(), 10, 0)));
			continue;
		}
		node = nodestartswith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replacestring(&(info->argv[i]),
				strdup_(strchr_(node->str, '=') + 1));
			continue;
		}
		replacestring(&info->argv[i], strdup_(""));

	}
	return (0);
}

/**
 * replacestring - replaces string - replaces string
 *
 * @old: address of old string
 *
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 *
 */

int replacestring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
