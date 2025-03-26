/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin_analyse_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:05:36 by abdael-m          #+#    #+#             */
/*   Updated: 2025/03/26 17:05:52 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsin_analyse_quotes(const char *command_line)
{
	if (utils_strstr(command_line, "\"") == NULL)
		return (SUCCESS);
	if (utils_docente(command_line, utils_strlen(command_line), '"'))
	{
		printf("minishell: syntax error\n");
		g_lastexitstatus = SYNTAX_ERROR;
		free((char *)command_line);
		return (FAILURE);
	}
	return (SUCCESS);
}
