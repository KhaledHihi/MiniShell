/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:10:17 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/03 15:30:26 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_cmd(char *input, char **env)
{
	t_token	*tokens;
	t_env	*lst_env;

	// split the command into tokens
	tokens = tokenize(input);
	if (!tokens)
		printf("syntax error\n");
	print_node(tokens);
	// store env variables in list
	lst_env = int_env(env);
	// print_lst(lst_env);
	(void)lst_env;
}
int	main(int ac, char *av[], char **env)
{
	char	*input;

	(void)env;
	(void)av;
	(void)ac;
	input = NULL;
	while (1)
	{
		input = readline("\033[1;92m➜  \033[1;36mminishell\033[0m ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		parsing_cmd(input, env);
		printf("You entered: %s\n", input);
		free(input);
	}
}
