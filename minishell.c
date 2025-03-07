/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:47:37 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/07 20:16:46 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int arc, char **arv)
{
	char	*command_line;
	char	*command_prompt;
	int		command_status;

	if (arc == 1 && arv)
	{
		command_status = 0;
		while (1)
		{
			command_prompt = readline_prompt(command_status);
			command_line = readline(command_prompt);
			if (command_line == NULL)
				return (free(command_prompt), 0);
			command_status = check_command_line(command_line);
			free(command_line);
			free(command_prompt);
		}
		return (0);
	}
	printf("\033[31mError\n\033[0m\033[32mRun:\033[0m \033[1;34m./minishell\033[0m\n");
	return (1);
}
