#include "minishell.h"

void	print_node(t_token *list)
{
	while (list)
	{
		printf("%s\n", list->value);
		printf("token_type : %d\n", list->token_type);
		printf("quote_type : %d\n", list->quote_type);
		printf("----------------------------\n");
		list = list->next;
	}
}
void	print_lst(t_env *list)
{
	while (list)
	{
		printf("lst key : %s\n", list->key);
		printf("lst value : %s\n", list->value);
		list = list->next;
	}
}

void	print_cmd(t_cmd *list)
{
	printf("test");
	while (list)
	{
		int i = 0;
		printf("Node:\n");
		if (list->arg)
		{
			while (list->arg[i])
			{
				printf("  arg[%d]: %s\n", i, list->arg[i]);
				i++;
			}
		}
		printf("-----------\n");
		list = list->next;
	}
}
