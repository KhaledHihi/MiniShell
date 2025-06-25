/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:10:17 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/25 15:09:26 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit;

int	only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] > 32)
			return (0);
		i++;
	}
	return (1);
}
void	parsing_cmd(char *input, char **env)
{
	t_token	*tokens;
	t_env	*lst_env;
	t_cmd	*cmd;

	(void)cmd;
	(void)lst_env;
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
	lst_env = int_env(env);
	expand_variables_and_remove_quotes(tokens, lst_env);
	cmd = prs_cmd(tokens);
	// print_node(tokens);
	print_cmd(cmd);

}
// void	read_line(t_list *env)
int	main(int ac, char *av[], char **env)
{
	char	*input;

	(void)ac;
	(void)av;
	input = NULL;
	while (1)
	{
		input = readline("\033[1;92m➜  \033[1;36mminishell\033[0m ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		if (only_spaces(input))
		{
			free(input);
			continue;
		}
		parsing_cmd(input, env);
		free(input);
	}
}
