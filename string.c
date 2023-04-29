#include "shell.h"

/**
 * _strlen - will return the length of a string
 * @f: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *f)
{
	int i = 0;

	if (!f)
		return (0);

	while (*f++)
		i++;
	return (i);
}

/**
 * _strcmp - will perform lexicogarphic comparison of two strangs.
 * @f1: the first strang
 * @f2: the second strang
 *
 * Return: negative if f1 < f2, positive if f1 > f2, zero if f1 == f2
 */
int _strcmp(char *f1, char *f2)
{
	while (*f1 && *f2)
	{
		if (*f1 != *f2)
			return (*f1 - *f2);
		f1++;
		f2++;
	}
	if (*f1 == *f2)
		return (0);
	else
		return (*f1 < *f2 ? -1 : 1);
}

/**
 * starts_with - function that checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - to concatenate two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
