/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:13:35 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/22 16:04:49 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_env_node(char *env_var)
{
	t_env	*new_env;
	char	*equal_address;
	int		key_length;

	new_env = ft_malloc(sizeof(t_env), 0);
	if (!new_env)
		return (NULL);
	equal_address = ft_strchr(env_var, '=');
	if (equal_address)
	{
		key_length = equal_address - env_var;
		new_env->key = ft_substr(env_var, 0, key_length);
		new_env->value = ft_strdup(equal_address + 1);
	}
	else
	{
		new_env->key = ft_strdup(env_var);
		new_env->value = NULL;
	}
	new_env->next = NULL;
	return (new_env);
}

void	append_env_node(t_env **lst, t_env *new_env)
{
	t_env	*tmp;

	if (!(*lst))
		*lst = new_env;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_env;
	}
}

t_env	*int_env(char **env)
{
	t_env	*lst;
	t_env	*new_env;
	int		i;

	lst = NULL;
	i = 0;
	while (env[i])
	{
		new_env = create_env_node(env[i]);
		if (!new_env)
			return (NULL);
		append_env_node(&lst, new_env);
		i++;
	}
	return (lst);
}
