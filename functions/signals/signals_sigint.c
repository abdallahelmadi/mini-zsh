/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_sigint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:33:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/26 17:42:56 by bnafiai          ###   ########.fr       */
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
