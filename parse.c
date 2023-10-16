#include "shell.h"

/**
 * stok - tokeneizer func
 * @lineptr: lineptr
 * @wrds: array storing tokens
 * @delim: delimiter for tokenization
 *
 * Return: No. of words
 */
int stok(char *lineptr, char ***wrds, char *delim)
{
	int wordCnt, i = 0;
	char *token;

	if (lineptr == NULL || wrds == NULL)
		return (-1);
	wordCnt = wrd_counter(lineptr);
	*wrds = (char **)malloc(sizeof(char *) * (wordCnt + 1));

	if (*wrds == NULL)
		return (-1);
	token = strtok(lineptr, delim);

	while (token != NULL)
	{
		(*wrds)[i] = _strdup(token);
		token = strtok(NULL, delim);

		if (token != NULL)
		{
			if (token[0] == '#')
				token = NULL;
		}
		i++;
	}
	(*wrds)[i] = NULL;

	return (wordCnt);
}

/**
 * getExecutablePath - builds path
 * @cmd: command
 *
 * Return: path
 */
char *getExecutablePath(char *cmd)
{
	char *fullpath = NULL, *bin = "/bin/";
	int i = 0, j = 0, direc_len;

	if (access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	if (cmd != NULL)
	{
		direc_len = _strlen(cmd) + _strlen(bin) + 1;
		fullpath = malloc(sizeof(char) * direc_len);

		if (fullpath != NULL)
		{
			while (i < direc_len - 1)
			{
				if (i < _strlen(bin))
				{
					fullpath[i] = bin[i];
				}
				else
				{
					fullpath[i] = cmd[j];

					j++;
				}
				i++;
			}

			free(cmd);
			cmd = NULL;
			fullpath[i] = '\0';

			return (fullpath);
		}
	}
	return (fullpath);
}
