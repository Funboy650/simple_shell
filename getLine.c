#include "shell.h"

/**
 * input_buf - This buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_y = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		x = getline(buf, &len_y, stdin);
#else
		x = _getline(info, buf, &len_y);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0'; /* remove trailing newline */
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
}

/**
 * get_input - This gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t a, b, len;
	ssize_t x = 0;
	char **buf_y = &(info->arg), *y;

	_putchar(BUF_FLUSH);
	x = input_buf(info, &buf, &len);
	if (x == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		b = a; /* init new iterator to current buf position */
		y = buf + a; /* get pointer for return */

		check_chain(info, buf, &b, a, len);
		while (b < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= len) /* reached end of buffer? */
		{
			a = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_y = y; /* pass back pointer to current command position */
		return (_strlen(y)); /* return length of current command */
	}

	*buf_y = buf; /* else not a chain, pass back buffer from _getline() */
	return (x); /* return length of buffer from _getline() */
}

/**
 * read_buf - function that reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - function that gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t l;
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

	c = _strchr(buf + i, '\n');
	l = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + l : l + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, l - i);
	else
		_strncpy(new_p, buf + i, l - i + 1);

	s += l - i;
	i = l;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
