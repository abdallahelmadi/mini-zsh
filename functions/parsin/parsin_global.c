/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_global.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:32:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/02 10:56:11 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_empty_string(const char *command_line)
{
	int	index;

	index = 0;
	while (command_line[index] != '\0')
	{
		if (command_line[index] != ' ')
			return (SUCCESS);
		index++;
	}
	return (free((char *)command_line), FAILURE);
}

void	parsin_global(const char *command_line)
{
	t_cmd_line	*cmd_list;

	cmd_list = NULL;
	g_lastexitstatus = SUCCESS;
	if (command_line[0] == '\0')
		return (free((char *)command_line));
	if (is_empty_string(command_line)
		|| parsin_forbidden_keywords(command_line)
		|| parsin_analyse_quotes(command_line))
		return ;
	parsin_make_list(command_line, &cmd_list);
	parsin_tokenization(&cmd_list);
}
