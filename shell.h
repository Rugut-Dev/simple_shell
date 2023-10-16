#ifndef MAIN_H
#define MAIN_H

extern char **environ;

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <stdarg.h>
#include <limits.h>

/**
 * struct llist - s linked list
 * @key: represents key
 * @add: represents address
 * @next: pointer to next node
 *
 */
typedef struct llist
{
	char *key;
	char *add;
	struct llist *next;
} sl_list;

int _print(char *str);
int main(void);
int isEmptyStr(const char *str);
int _strlen(char *str);
int wrd_counter(char *str);
int execute(char **args);
char *_getenv(const char *key);
char *_strdup(char *str);
int _strcmp(const char *str1, const char *str2);
char *getExecutablePath(char *cmd);
sl_list *insert_node(char *key, char *add);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int notFound(void);
int _setenv(char *name, char *value);
int delete_node(const char *key);
void free_list(sl_list *head);
int stok(char *lineptr, char ***wrds, char *delim);
void explicit_free(char ***wrds, int wordCnt);
int _unsetenv(const char *name);
int builtins(char **args);
void free_env(void);
void exit_checker(char **args,
		int wordCount, int *exitStatus, int *prevExitStatus);
void exit_builtin(char **args,
		int wordCount, int *exitStatus, int *prevExitStatus);
void cd(char *path);

#endif
