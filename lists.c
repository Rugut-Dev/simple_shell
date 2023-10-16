#include "shell.h"
static sl_list *head;

/**
 * insert_node - inserts node
 * @key: variable name
 * @add: address
 *
 * Return: list
 */
sl_list *insert_node(char *key, char *add)
{
	sl_list *newNode;

	newNode = malloc(sizeof(sl_list));

	if (newNode != NULL)
	{
		newNode->key = _strdup(key);
		newNode->add = add;
		newNode->next = head;
		head = newNode;

		return (newNode);
	}
	else
		return (NULL);
}

/**
 * delete_node - deletes node
 * @key: name of variable
 *
 * Return: lis
 */
int delete_node(const char *key)
{
	sl_list *cur_node, *prev_node;

	if (head != NULL)
	{
		prev_node = head;

		while (prev_node != NULL)
		{
			cur_node = prev_node->next;

			if (_strcmp(key, cur_node->key) == 0)
			{
				prev_node->next = cur_node->next;
				free(cur_node->add);
				free(cur_node->key);
				free(cur_node);

				cur_node = NULL;

				return (0);
			}
			prev_node = prev_node->next;
		}
	}
	return (-1);
}

/**
 * free_list - frees a whole list
 * @head: head node
 *
 */
void free_list(sl_list *head)
{
	sl_list *cur_node, *next_node;

	cur_node = head;

	while (cur_node != NULL)
	{
		next_node = cur_node->next;

		free(cur_node->add);
		free(cur_node->key);
		free(cur_node);

		cur_node = next_node;
	}
}

/**
 * free_env - helper
 */
void free_env(void)
{
	if (head != NULL)
		free_list(head);
}
