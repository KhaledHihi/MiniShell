/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signales_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:33 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/02 18:22:10 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		g_exit = 130;
		ft_malloc(0, 1);
		ft_exit(g_exit);
	}
}

void	handle_here_doc_signals(void)
{
	signal (SIGQUIT, SIG_IGN);
	signal (SIGINT, sig_handler_here_doc);
}
