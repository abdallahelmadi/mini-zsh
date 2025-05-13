/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_s1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:33:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/09 16:38:55 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_global.g_signal = 1;
	}
}

void	signals_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (!g_global.g_foreground_running)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			utils_setexit(SIGNAL_SIGINT);
		}
		else
		{
			write(1, "\n", 1);
			utils_setexit(SIGNAL_SIGINT);
		}
	}
}

void	setup_signals_main(void)
{
	signal(SIGINT, signals_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	restore(void)
{
	setup_signals_main();
}

void	setup_for_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
