#include "minishell.h"

void print_node(t_token *list)
{
	while(list)
	{
		printf("%s\n", list->value);
		list = list->next;
	}
}
