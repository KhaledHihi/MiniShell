/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:45:30 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/02 18:22:52 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(int nb)
{
	ft_malloc(0, 1);
	exit(nb);
}

char	*get_tmp_file(void)
{
	char		*file_name;
	char		*tmpfile;
	static int	i;
	char		*heredoc_name;

	heredoc_name = "heredoc_";
	file_name = ft_strjoin(heredoc_name, ft_itoa(i));
	tmpfile = ft_strjoin("/tmp/", file_name);
	i++;
	return (tmpfile);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

char	**copy_env(char **envp)
{
	char	**new_env;
	int		i;

	i = 0;
	while (envp && envp[i])
		i++;
	new_env = ft_malloc(sizeof(char *) * (i + 1), 0);
	if (!new_env)
	{
		perror("malloc: ");
		return (NULL);
	}
	i = 0;
	while (envp && envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			perror("ft_strdup: ");
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	update_shell_level(t_exec_env *exec_env)
{
	char	*tmp;
	int		value;
	char	*new_value;
	int		index_var;

	if (search_for_env_var(exec_env->env, "SHLVL"))
	{
		index_var = get_env_var_index(exec_env->env, "SHLVL");
		value = ft_atoi(ft_strchr(exec_env->env[index_var], '=') + 1);
		if (value < 0)
			ft_strdup("SHLVL=0");
		else if (value > 999)
		{
			printf("%s%d%s", "minishell: warning: shell level(",
				value, ") too high, resetting to 1\n");
			exec_env->env[index_var] = ft_strdup("SHLVL=1");
		}
		else
		{
			++value;
			new_value = ft_itoa(value);
			tmp = ft_strjoin("SHLVL=", new_value);
			exec_env->env[index_var] = ft_strdup(tmp);
		}
	}
}
