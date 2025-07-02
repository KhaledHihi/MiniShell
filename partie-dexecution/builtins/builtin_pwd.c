/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:01 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/02 18:25:34 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_pwd(char **env)
{
	int		pwd_index;
	char	*cwd;

	if (search_for_env_var(env, "PWD"))
	{
		pwd_index = get_env_var_index(env, "PWD");
		if ((env[pwd_index] + 4)[0] != '\0')
			printf("%s\n", env[pwd_index] + 4);
		else
		{
			cwd = getcwd(NULL, 0);
			printf("%s\n", cwd);
			free(cwd);
		}
	}
	else
	{
		cwd = getcwd(NULL, 0);
		printf("%s\n", cwd);
		free(cwd);
	}
	return (EXIT_SUCCESS);
}
