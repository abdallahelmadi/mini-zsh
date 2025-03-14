/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:32:31 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/14 17:28:51 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd_line	*split_command_as_list(const char *command_line)
{
	char	**temp;

	temp = utils_split(command_line, '|');
	return (NULL);
}

void	check_command_line(const char *command_line)
{
	t_cmd_line	*cmd_list;

	if (command_line[0] == '\0')
		return ;
	else if (!utils_strcmp(command_line, '&') || utils_strstr(command_line, ">>>")
		|| !utils_strcmp(command_line, '(') || !utils_strcmp(command_line, ')')
		|| !utils_strcmp(command_line, '*') || !utils_strcmp(command_line, ';')
		|| utils_strstr(command_line, "<<<") || !utils_strcmp(command_line, '#')
		|| !utils_strcmp(command_line, '\\')
		|| utils_strstr(command_line, "||"))
	{
		printf("minishell: something unsupported\n");
		g_lastexitstatus = FAILURE;
	}
	else
	{
		cmd_list = split_command_as_list(command_line);
		while (cmd_list != NULL)
		{
			printf("Type: %s, value: %s\n", cmd_list->type, cmd_list->value);
			cmd_list = cmd_list->next;
		}
		g_lastexitstatus = SUCCESS;
	}
}
