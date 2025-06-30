/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:55:05 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/30 19:05:05 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	custom_error(char *err_msg, char *arg, int exit_code, int is_builtin)
{
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	if (!is_builtin)
	{
		ft_malloc(0, 1);
		ft_exit(exit_code);
	}
	return (exit_code);
}
