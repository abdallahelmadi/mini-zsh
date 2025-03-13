/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:47:37 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/13 15:32:37 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_lastexitstatus = 0;

static void	handle_signals(void)
{
	signal(SIGINT, signals_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int arc, char **arv)
{
	char	*command_line;
	char	*command_prompt;

	if (arc == 1 && arv)
	{
		handle_signals();
		while (1)
		{
			command_prompt = readline_prompt();
			command_line = readline(command_prompt);
			if (command_line == NULL)
				return (printf("exit\n"), free(command_prompt),
					rl_clear_history(), SUCCESS);
			if (command_line[0] != '\0')
				add_history(command_line);
			check_command_line(command_line);
			free(command_line);
			free(command_prompt);
		}
	}
	return (FAILURE);
}
