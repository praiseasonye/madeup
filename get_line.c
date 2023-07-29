/**
 * input_buf - buffers chained commands
 *
 * @info: parameter struct
 *
 * @buf: address of buffer
 *
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t input_buf(Shell *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) 
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			removecomments(*buf);
			buildhistorylist(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 *
 * @info: parameter struct
 *
 * Return: bytes read
 *
 */

ssize_t get_input(Shell *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMDNORM;
		}

		*buf_p = p;
		return (strlen_(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * _getline - get the next line of input from STDIN
 *
 * @info: parameter struct
 *
 * @ptr: address of pointer to buffer, preallocated or NULL
 *
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(Shell *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strchr_(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc_(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		strncat_(new_p, buf + i, k - i);
	else
		strncpy_(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 *
 * @sig_num: the signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	puts("\n");
	puts("$ ");
	putchar(BUFF_FLUSH);
}
