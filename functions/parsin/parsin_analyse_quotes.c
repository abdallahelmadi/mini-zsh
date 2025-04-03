/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_analyse_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:05:36 by abdael-m          #+#    #+#             */
/*   Updated: 2025/04/03 10:02:02 by abdael-m         ###   ########.fr       */
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

static void	print_error_message(char c)
{
	printf("minishell: syntax error, looking for matching `%c`\n", c);
	utils_setexit(SYNTAX_ERROR);
}

int	parsin_analyse_quotes(const char *command_line)
{
	int (squotes), (dquotes), (index);
	if (utils_strstr(command_line, "\"") == NULL
		&& utils_strstr(command_line, "'") == NULL)
		return (SUCCESS);
	squotes = 0;
	dquotes = 0;
	index = -1;
	while (command_line[++index] != '\0')
	{
		if (command_line[index] == '\''
			&& (dquotes > 1 || dquotes == 0) && dquotes % 2 == 0)
			squotes++;
		else if (command_line[index] == '\"'
			&& (squotes > 1 || squotes == 0) && squotes % 2 == 0)
			dquotes++;
	}
	if (dquotes == 1 || dquotes % 2 != 0)
		return (print_error_message('\"'), free((char *)command_line), FAILURE);
	if (squotes == 1 || squotes % 2 != 0)
		return (print_error_message('\''), free((char *)command_line), FAILURE);
	return (handle_spliters_inside_quotes((char *)command_line), SUCCESS);
}
