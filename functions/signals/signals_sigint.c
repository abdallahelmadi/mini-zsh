/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_sigint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:33:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/08 17:34:00 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signals_sigint(int sig)
{
	(void)sig;
	// rl_on_new_line();
	// rl_replace_line("test", 1);
	// rl_redisplay();
}
