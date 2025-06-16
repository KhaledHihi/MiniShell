/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:10:17 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/16 18:38:54 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit;

void	parsing_cmd(char *input, char **env)
{
	t_token	*tokens;
	t_env	*lst_env;
	t_cmd	*cmd;

	(void)lst_env;
	(void)env;
	(void)cmd;
	(void)env;
	if ((input == NULL || !ft_strncmp(input, "exit", 4))
		&& (ft_strlen(input) == 4))
	{
		printf("\033[1;31mexit\033[0m\n");
		ft_malloc(0, 1);
		free(input);
		exit(0);
	}
	tokens = tokenize(input);
	if (!tokens)
	{
		printf("\033[1;31mSyntax Error\033[0m\n");
		return ;
	}
	// store env variables in list
	lst_env = int_env(env);
	// print_lst(lst_env);
	cmd = prs_cmd(tokens);
	expand_variables_and_remove_quotes(tokens, lst_env);
	print_node(tokens);
	print_cmd(cmd);
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
