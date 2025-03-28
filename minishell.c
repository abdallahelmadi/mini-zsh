/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:47:37 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/17 17:24:12 by bnafiai          ###   ########.fr       */
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
			command_prompt = readline_prompt();
			command_line = readline(command_prompt);
			if (command_line == NULL)
				return (printf("exit\n"), free(command_prompt),
					rl_clear_history(), SUCCESS);
			if (command_line[0] != '\0')
				add_history(command_line);
			check_command_line(command_line);
			// fun_echo(command_line);
			// fun_env(command_line);
			// fun_exit(command_line);
			// fun_pwd(command_line);
			// fun_cd(command_line);
			fun_export(command_line);
			fun_unset(command_line);
			free(command_line);
			free(command_prompt);
		}
	}
	return (FAILURE);
}
