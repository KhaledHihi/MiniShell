/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:43:51 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/02 15:57:11 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../minishell.h"

static int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg)
	{
		if ((arg[0] == '+' && !ft_isdigit(arg[1]))
			|| (arg[0] == '-' && !ft_isdigit(arg[1])) || !(ft_isdigit(arg[0])))
			return (0);
		i = 1;
	}
	while (arg && arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char	**args, int last_cmd_exit_status)
{
	if (!args[1])
		return (last_cmd_exit_status);
	if (!args[1][0] || !is_numeric(args[1]))
	{
		ft_putstr_fd("bash: exit: numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	if (args[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return ((unsigned char)ft_atoi(args[1]));
}
