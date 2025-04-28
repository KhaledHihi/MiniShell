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
