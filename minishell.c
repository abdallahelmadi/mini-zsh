/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:47:37 by abdael-m          #+#    #+#             */
/*   Updated: 2025/05/06 11:09:23 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	g_global = {SUCCESS, SUCCESS, NULL, SUCCESS, SUCCESS, NULL};

int	main(int arc, char **arv, char **env)
{
	char	*command_line;

	g_global.g_environments = utils_gsetenv((const char **)env);
	if (arc == 1 && arv)
	{
		setup_signals_main();
		while (1)
		{
			command_line = readline(prompt_zsh());
			if (command_line == NULL)
				return (printf("exit\n"), rl_clear_history(),
					smalloc(-1), SUCCESS);
			if (command_line[0] != '\0')
				add_history(command_line);
			else
			{
				free(command_line);
				continue ;
			}
			parsin_global(command_line);
		}
		smalloc(-1);
	}
	return (FAILURE);
}
