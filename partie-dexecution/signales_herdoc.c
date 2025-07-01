/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signales_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:33 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/01 15:25:01 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/minishell.h"

void	sig_handler_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		g_exit_status = 130;
		ft_malloc(0, 0);
		ft_exit(g_exit_status);
	}
}

void	handle_here_doc_signals(void)
{
	signal (SIGQUIT, SIG_IGN);
	signal (SIGINT, sig_handler_here_doc);
}
