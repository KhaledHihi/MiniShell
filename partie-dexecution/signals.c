/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:45:24 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/01 23:48:47 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

void	sig_handler_parent(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit = 130;
}

void	sig_handler_child(int signum)
{
	if (signum == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		g_exit = 131;
	}
	if (signum == SIGINT)
	{
		printf("\n");
		g_exit = 130;
	}
}

void	handle_parent_signals(void)
{
	signal (SIGQUIT, SIG_IGN);
	signal (SIGINT, sig_handler_parent);
}

void	handle_child_signals(void)
{
	signal(SIGQUIT, sig_handler_child);
	signal(SIGINT, sig_handler_child);
}
