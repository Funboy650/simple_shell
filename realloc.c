#include "shell.h"

/**
 **_memset - function that fills memory with a constant byte
 *@s: the pointer to the memory area
 *@h: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char h, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = h;
	return (s);
}

/**
 * ffree - function that frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **r = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(r);
}

/**
 * _realloc - function that reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *y;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	y = malloc(new_size);
	if (!y)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		y[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (y);
}
