#include "minishell.h"

void print_node(t_token *list)
{
	while(list)
	{
		printf("%s\n", list->value);
		printf("token_type : %d\n", list->token_type);
		printf("quote_type : %d\n", list->quote_type);
		printf("----------------------------\n");
		list = list->next;
	}
}
void print_lst(t_env *list)
{
	while(list)
	{
		printf("lst key : %s\n", list->key);
		printf("lst value : %s\n", list->value);
		list = list->next;
	}
}
