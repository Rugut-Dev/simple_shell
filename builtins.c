#include "shell.h"

/**
 * builtins - checks for buiiltin function
 * @args: array of tokens from cmdline
 *
 * Return: exitStatus
 */
int builtins(char **args)
{
	int exitStatus;

	if (_strcmp(args[0], "setenv") == 0
			&& args[1] != NULL && args[2] != NULL)
	{
		exitStatus = _setenv(args[1], args[2]);
	}
	else if ((_strcmp(args[0], "unsetenv") == 0)
			&& args[1] != NULL)
		exitStatus = _unsetenv(args[1]);
	else if (_strcmp(args[0], "cd") == 0)
		cd(args[1]);
	else if (_strcmp(args[0], "exit") == 0 || _strcmp(args[0], "#") == 0)
	{

	}
	else
		exitStatus = execute(args);
	return (exitStatus);
}

/**
 * exit_builtin - exit builtin func
 * @args: array of tokens from cmd
 * @wordCount: no of words passed from cmd
 * @exitStatus: current exitStatus
 * @prevExitStatus: previous command's exit status
 *
 */
void exit_builtin(char **args, int wordCount,
		  int *exitStatus, int *prevExitStatus)
{
	int status;
	char *errorMsg;
	size_t msgLen, argLen;

	if (wordCount > 1)
	{
		status = atoi(args[1]);

		if ((status == 0 && _strcmp(args[1], "0") != 0) || status < 0)
		{
			errorMsg = "./hsh: 1: exit: Illegal number: ";
			msgLen = _strlen(errorMsg);
			argLen = _strlen(args[1]);

			write(2, errorMsg, msgLen);
			write(2, args[1], argLen);
			write(2, "\n", 1);
			explicit_free(&args, wordCount);
			free_env();
			exit(2);
		} else
			*exitStatus = status;
	} else
		*exitStatus = *prevExitStatus;

	explicit_free(&args, wordCount);
	free_env();

	exit(*exitStatus);
}

/**
 * _setenv - custom setenv
 * @name: name of env variable
 * @value: val of env variable
 *
 * Return: exitStatus
 */
int _setenv(char *name, char *value)
{
	int size, i = 0;
	char *env, *token, *env_new;

	size = _strlen(name) + _strlen(value) + 2;
	env_new = (char *)malloc(sizeof(char) * size);
	if (env_new != NULL)
	{
		_strcpy(env_new, name);
		_strcat(env_new, "=");
		_strcat(env_new, value);
		while (environ[i])
		{
			env = _strdup(environ[i]);
			token = strtok(env, "=");
			if (token != NULL && _strcmp(token, name) == 0)
			{
				environ[i] = _strdup(env_new);

				insert_node(name, environ[i]);
				free(env);
				break;
			}
			if ((token != NULL && _strcmp(token, name) != 0)
			    && environ[i + 1] == NULL)
			{
				environ[i + 1] = _strdup(env_new);

				insert_node(name, environ[i + 1]);
				environ[i + 2] = NULL;

				free(env);
				break;
			}
			i++;
			free(env);
		}
		free(env_new);
	} else
		return (-1);
	return (i);
}

/**
 * _unsetenv - custom unsetenv
 * @name: name of env variable
 *
 * Return: exit status
 */
int _unsetenv(const char *name)
{
	int i = 0;
	char *env, *token;

	while (environ[i])
	{
		env = _strdup(environ[i]);
		token = strtok(env, "=");

		if (_strcmp(token, name) == 0)
		{
			while (environ[i + 1] != NULL)
			{
				environ[i] = environ[i + 1];

				i++;
			}
			environ[i] = NULL;
			delete_node(name);
		}
		i++;
		free(env);
	}
	if (environ[i] != NULL)
	{
		perror("unsetenv failed terribly");
	}
	return (i);
}

/**
 * cd -cd builtin
 * @path: arg after cd cmd
 *
 */
void cd(char *path)
{
	char previous_path[1000], *errMsg1, *errMsg2;

	if (path == NULL || _strcmp(path, "~") == 0)
	{
		path = _getenv("HOME");
		if (path == NULL)
			return;
	} else if (_strcmp(path, "-") == 0)
	{
		path = _getenv("OLDWD");
		if (path != NULL)
		{
			_print(path);
			_print("\n");
		} else
		{
			errMsg1 = "chgdir: No previous directory\n";
			write(STDERR_FILENO, errMsg1, strlen(errMsg1));
			return;
		}
	}
	if (path != NULL)
	{
		getcwd(previous_path, sizeof(previous_path));
		if (chdir(path) == 0)
		{
			_setenv("OLDWD", previous_path);
			_setenv("PWD", path);
		} else
		{
			errMsg1 = "./hsh: 1: cd: can't cd to ";
			write(STDERR_FILENO, errMsg1, _strlen(errMsg1));
			write(STDERR_FILENO, path, _strlen(path));
			write(STDERR_FILENO, "\n", 1);
		}
	} else
	{
		errMsg2 = "chgdir: Invalid path or environment variable not set\n";
		write(STDERR_FILENO, errMsg2, _strlen(errMsg2));
	}
}
