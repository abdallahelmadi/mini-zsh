/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:47:37 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/04 14:52:50 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_lastexitstatus = SUCCESS;

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
			command_prompt = prompt_zsh();
			command_line = readline(command_prompt);
			free(command_prompt);
			if (command_line == NULL)
				return (printf("exit\n"), rl_clear_history(), SUCCESS);
			if (command_line[0] != '\0')
				add_history(command_line);
			// fun_cd(command_line);
			// fun_pwd(command_line);
			parsin_global(command_line);
		}
	}
	return (FAILURE);
}
