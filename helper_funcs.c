#include "shell.h"

/**
 * _print - custom write function
 * @str: string
 *
 * Return: len of char printed or -1 on failure
 */
int _print(char *str)
{
	int count = -1;

	if (str != NULL)
	{
		count = write(1, str, _strlen(str));
	}
	return (count);
}

/**
 * wrd_counter - counts words in lineptr
 * @str: lineptr
 *
 * Return: count
 */
int wrd_counter(char *str)
{
	int cnt = 0, i = 0;
	char delim = ' ';

	while (str[i] != '\0')
	{
		if (str[i] != delim)
		{
			cnt++;
			while (str[i] != '\0' && str[i] != delim)
			{
				if (str[i + 1] == delim)
				{
					i++;
					continue;
				}
				i++;
			}
		} else
		{
			i++;
		}
	}
	if (str[i - 1] == delim)
		cnt--;

	return (cnt);
}

/**
 * explicit_free - frees wrds array
 * @wrds: tokens
 * @wordCnt: no of tokens
 *
 */
void explicit_free(char ***wrds, int wordCnt)
{
	if (*wrds != NULL && wordCnt > 0)
	{
		int i;

		for (i = 0; i < wordCnt; i++)
		{
			free((*wrds)[i]);
			(*wrds)[i] = NULL;
		}
		free(*wrds);
		*wrds = NULL;
		wordCnt = 0;
	}
}

/**
 * isEmptyStr - isempty customized
 * @str: string to be checked
 *
 * Return: 1 if empty or 0 if not
 */
int isEmptyStr(const char *str)
{
	if (str == NULL)
		return (1);

	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\t' && *str != '\n'
				&& *str != '\r' && *str != '\f' && *str != '\v')
		{
			return (0);
		}
		str++;
	}
	return (1);
}

/**
 * exit_checker - checks for exit string
 * @args: array of tokens from cmd
 * @wordCount: no of words passed from cmd
 * @exitStatus: current exitStatus
 * @prevExitStatus: previous command's exit status
 *
 */
void exit_checker(char **args, int wordCount,
		int *exitStatus, int *prevExitStatus)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		exit_builtin(args, wordCount, exitStatus, prevExitStatus);
	}
}
