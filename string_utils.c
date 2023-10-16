#include "shell.h"

/**
 * _strlen - custom strlen
 * @str: string pointer
 *
 * Return: 0
 */
int _strlen(char *str)
{
	int len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

/**
 * _strcpy - strcpy custom
 * @dest: copy destination
 * @src: copy source
 *
 * Return: output string
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	while (*(src + i) != '\0')
	{
		i++;
	}
	for ( ; j < i ; j++)
	{
		dest[j] = src[j];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strdup - custom strdup
 * @str: chars to be dup'ed
 *
 * Return: pointer to malloc'ed
 */

char *_strdup(char *str)
{
	char *output;
	unsigned int i, j;

	if (str == NULL)
	{
		return (NULL);
	}

	for (i = 0; str[i] != '\0'; i++)
		;

	output = (char *)malloc(sizeof(char) * (i + 1));

	if (output == NULL)
		return (NULL);

	for (j = 0; j <= i; j++)
	{
		output[j] = str[j];
	}
	return (output);
}

/**
 * _strcmp - custom strcmp
 * @str1: string 1
 * @str2: string 2
 *
 * Return: 0 if strings are simlar
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

/**
 * _strcat - custom strcat
 * @dest: destination
 * @src: source
 *
 * Return: output string
 */
char *_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return (dest);
}
