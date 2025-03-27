/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_analyse_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:05:36 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/27 15:42:47 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_spliters_inside_quotes(char *command_line)
{
	int (quote), (index);
	index = -1;
	while (command_line[++index] != '\0')
	{
		quote = (utils_docente(command_line, index, '"')
				|| utils_docente(command_line, index, '\'') || 0);
		if (command_line[index] == '|' && quote)
			command_line[index] = 1;
		else if (utils_strstr_pro(&(command_line[index]), ">>") && quote)
		{
			command_line[index] = 2;
			command_line[index + 1] = 2;
		}
		else if (utils_strstr_pro(&(command_line[index]), "<<") && quote)
		{
			command_line[index] = 3;
			command_line[index + 1] = 3;
		}
		else if (command_line[index] == '<' && quote)
			command_line[index] = 4;
		else if (command_line[index] == '>' && quote)
			command_line[index] = 5;
		else if (command_line[index] == ' ' && quote)
			command_line[index] = 6;
	}
}

int	parsin_analyse_quotes(const char *command_line)
{
	int (counter), (index);
	if (utils_strstr(command_line, "\"") == NULL
		&& utils_strstr(command_line, "'") == NULL)
		return (SUCCESS);
	if (utils_docente(command_line, utils_strlen(command_line), '"'))
	{
		printf("minishell: syntax error, looking for matching '\"'\n");
		g_lastexitstatus = SYNTAX_ERROR;
		return (free((char *)command_line), FAILURE);
	}
	index = -1;
	counter = 0;
	while (command_line[++index] != '\0')
	{
		if (command_line[index] == '\''
			&& utils_docente(command_line, index, '"') == 0)
			counter++;
	}
	if (counter == 1 || (counter > 1 && counter % 2 != 0))
	{
		printf("minishell: syntax error, looking for matching '\''\n");
		g_lastexitstatus = SYNTAX_ERROR;
		return (free((char *)command_line), FAILURE);
	}
	return (handle_spliters_inside_quotes((char *)command_line), SUCCESS);
}
