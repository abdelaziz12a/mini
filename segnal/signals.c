/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaboudra <aaboudra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 03:18:23 by aaboudra          #+#    #+#             */
/*   Updated: 2025/07/13 23:40:44 by aaboudra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

void	_sigint_handler(int sig)
{
	(void)sig;
	if (SIGINT && (g_sigint_received != 555
			&& g_sigint_received != 600
			&& g_sigint_received != 700 && g_sigint_received != 1))
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_init(void)
{
	signal(SIGINT, _sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
