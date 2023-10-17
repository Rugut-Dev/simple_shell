#include "shell.h"

/**
 * main - custom shell(hsh)
 *
 * Return: exit status
 */
int main(void)
{
	char *lineptr = NULL, **wrds = NULL, *delim = " \n";
	size_t len = 0;
	int int_active = isatty(STDIN_FILENO),
	    wordCnt, exitStatus = 0, prevExitStatus = 0;

	if (int_active == 1)
		_print("$ ");
	while (getline(&lineptr, &len, stdin) != -1)
	{
		if (isEmptyStr(lineptr) == 0)
		{
			wordCnt = stok(lineptr, &wrds, delim);

			free(lineptr);

			lineptr = NULL;
			exitStatus = builtins(wrds);

			exit_checker(wrds, wordCnt,
					&exitStatus, &prevExitStatus);
			explicit_free(&wrds, wordCnt);
		}
		if (int_active == 1)
			_print("$ ");
		prevExitStatus = exitStatus;
	}
	if (lineptr)
		free(lineptr);
	if (int_active == 1)
		_print("\n");

	return (exitStatus);
}

/**
 * execute - execve func
 * @args: tokens from stok
 *
 * Return: exit status
 */
int execute(char **args)
{
	pid_t childPid;
	int execResult, exitStatus, childStatus;

	args[0] = getExecutablePath(args[0]);
	if (access(args[0], X_OK | F_OK) == 0)
	{
		childPid = fork();

		if (childPid == -1)
		{
			perror("./hsh");
			exitStatus = 2;

			return (-1);
		}
		if (childPid != 0)
		{
			wait(&childStatus);
			if (WIFEXITED(childStatus))
				exitStatus = WEXITSTATUS(childStatus);

		} else
		{
			execResult = execve(args[0], args, environ);

			if (execResult == -1)
			{
				perror("./hsh");
				exitStatus = 2;

				exit(-1);
			}
		}
	} else
	{
		exitStatus = notFound();

		return (2);
	}
	return (exitStatus);
}
/**
 * notFound - notFound helper
 *
 * Return: 2
 */
int notFound(void)
{
	errno = ENOENT;

	perror("./hsh");
	return (2);
}


/**
 * _getenv - custom getenv
 * @key: name of key
 *
 * Return: value of key
 */
char *_getenv(const char *key)
{
	char *env, *token;
	int i = 0, j = 0;

	while (environ[i])
	{
		env = _strdup(environ[i]);
		token = strtok(env, "=");

		if (_strcmp(token, key) == 0)
		{
			token = strtok(NULL, "=");

			free(env);
			while ((environ[i])[j] != '=')
				j++;
			j++;
			token = (&(environ[i])[j]);

			return (token);
		}
		i++;
		free(env);
	}
	return (NULL);
}
