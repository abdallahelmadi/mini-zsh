/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_sigint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:33:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/02 17:07:10 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handler_heredoc(int sig)
{
	(void)sig;
	g_global.g_signal = 1;
	write(1, "\n", 1);
}
void	signals_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	utils_setexit(SIGNAL_SIGINT);
}
void	signals_sigquit(int sig)
{
	(void)sig;
	printf("\nQUIT\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	setup_signals(void)
{
	struct sigaction sa_int, sa_quit;

	sa_int.sa_handler = signals_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = signals_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
void	disable_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
void	restore(void)
{
	setup_signals();
}
