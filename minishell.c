/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:47:37 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/05 08:46:59 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	g_global = {SUCCESS, NULL};

static void	handle_signals(void)
{
	signal(SIGINT, signals_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int arc, char **arv, char **env)
{
	char	*command_line;
	char	*command_prompt;

	utils_gsetenv((const char **)env);
	if (arc == 1 && arv)
	{
		handle_signals();
		while (1)
		{
			command_prompt = prompt_zsh();
			command_line = readline(command_prompt);
			free(command_prompt);
			if (command_line == NULL)
				return (printf("exit\n"), rl_clear_history(),
					utils_free(utils_gsetenv(NULL)), SUCCESS);
			if (command_line[0] != '\0')
				add_history(command_line);
			parsin_global(command_line);
		}
	}
	return (FAILURE);
}
