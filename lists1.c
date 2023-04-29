#include "shell.h"

/**
 * list_len -function that  determines length of linked list
 * @k: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *k)
{
	size_t a = 0;

	while (k)
	{
		k = k->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - to return an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - This prints all elements of a list_t linked list
 * @k: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *k)
{
	size_t a = 0;

	while (k)
	{
		_puts(convert_number(k->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(k->str ? k->str : "(nil)");
		_puts("\n");
		k = k->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - This returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @g: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char g)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((g == -1) || (*p == g)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Function that gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
